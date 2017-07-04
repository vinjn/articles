// https://stackoverflow.com/questions/8004945/how-to-catch-a-memory-write-and-call-function-with-address-of-write
// compile with Open Watcom 1.9: wcl386 wrtrap.c

#include <windows.h>
#include <stdio.h>

#ifndef PAGE_SIZE
#define PAGE_SIZE 4096
#endif


UINT_PTR RangeStart = 0;
SIZE_T RangeSize = 0;

UINT_PTR AlignedRangeStart = 0;
SIZE_T AlignedRangeSize = 0;


void MonitorRange(void* Start, size_t Size)
{
  DWORD dummy;

  if (Start &&
      Size &&
      (AlignedRangeStart == 0) &&
      (AlignedRangeSize == 0))
  {
    RangeStart = (UINT_PTR)Start;
    RangeSize = Size;

    // Page-align the range address and size

    AlignedRangeStart = RangeStart & ~(UINT_PTR)(PAGE_SIZE - 1);

    AlignedRangeSize = ((RangeStart + RangeSize - 1 + PAGE_SIZE) &
                        ~(UINT_PTR)(PAGE_SIZE - 1)) -
                       AlignedRangeStart;

    // Make the page range read-only
    VirtualProtect((LPVOID)AlignedRangeStart, 
                   AlignedRangeSize,
                   PAGE_READONLY,
                   &dummy);
  }
  else if (((Start == NULL) || (Size == 0)) &&
           AlignedRangeStart &&
           AlignedRangeSize)
  {
    // Restore the original setting
    // Make the page range read-write
    VirtualProtect((LPVOID)AlignedRangeStart,
                   AlignedRangeSize,
                   PAGE_READWRITE,
                   &dummy);

    RangeStart = 0;
    RangeSize = 0;

    AlignedRangeStart = 0;
    AlignedRangeSize = 0;
  }
}

// This is where the magic happens...
int ExceptionFilter(LPEXCEPTION_POINTERS pEp,
                    void (*pMonitorFxn)(LPEXCEPTION_POINTERS, void*))
{
  CONTEXT* ctx = pEp->ContextRecord;
  ULONG_PTR* info = pEp->ExceptionRecord->ExceptionInformation;
  UINT_PTR addr = info[1];
  DWORD dummy;

  switch (pEp->ExceptionRecord->ExceptionCode)
  {
  case STATUS_ACCESS_VIOLATION:
    // If it's a write to read-only memory,
    // to the pages that we made read-only...
    if ((info[0] == 1) &&
        (addr >= AlignedRangeStart) &&
        (addr < AlignedRangeStart + AlignedRangeSize))
    {
      // Restore the original setting
      // Make the page range read-write
      VirtualProtect((LPVOID)AlignedRangeStart,
                     AlignedRangeSize,
                     PAGE_READWRITE,
                     &dummy);

      // If the write is exactly within the requested range,
      // call our monitoring callback function
      if ((addr >= RangeStart) && (addr < RangeStart + RangeSize))
      {
        pMonitorFxn(pEp, (void*)addr);
      }

      // Set FLAGS.TF to trigger a single-step trap after the
      // next instruction, which is the instruction that has caused
      // this page fault (AKA access violation)
      ctx->EFlags |= (1 << 8);

      // Execute the faulted instruction again
      return EXCEPTION_CONTINUE_EXECUTION;
    }

    // Don't handle other AVs
    goto ContinueSearch;

  case STATUS_SINGLE_STEP:
    // The instruction that caused the page fault
    // has now succeeded writing to memory.
    // Make the page range read-only again
    VirtualProtect((LPVOID)AlignedRangeStart,
                   AlignedRangeSize,
                   PAGE_READONLY,
                   &dummy);

    // Continue executing as usual until the next page fault
    return EXCEPTION_CONTINUE_EXECUTION;

  default:
  ContinueSearch:
    // Don't handle other exceptions
    return EXCEPTION_CONTINUE_SEARCH;
  }
}


// We'll monitor writes to blah[1].
// volatile is to ensure the memory writes aren't
// optimized away by the compiler.
volatile int blah[3] = { 3, 2, 1 };

void WriteToMonitoredMemory(void)
{
  blah[0] = 5;
  blah[0] = 6;
  blah[0] = 7;
  blah[0] = 8;

  blah[1] = 1;
  blah[1] = 2;
  blah[1] = 3;
  blah[1] = 4;

  blah[2] = 10;
  blah[2] = 20;
  blah[2] = 30;
  blah[2] = 40;
}

// This pointer is an attempt to ensure that the function's code isn't
// inlined. We want to see it's this function's code that modifies the
// monitored memory.
void (* volatile pWriteToMonitoredMemory)(void) = &WriteToMonitoredMemory;

void WriteMonitor(LPEXCEPTION_POINTERS pEp, void* Mem)
{
  printf("We're about to write to 0x%X from EIP=0x%X...\n",
         Mem,
         pEp->ContextRecord->Eip);
}

int main(void)
{
  printf("&WriteToMonitoredMemory() = 0x%X\n", pWriteToMonitoredMemory);
  printf("&blah[1] = 0x%X\n", &blah[1]);

  printf("\nstart\n\n");

  __try
  {
    printf("blah[0] = %d\n", blah[0]);
    printf("blah[1] = %d\n", blah[1]);
    printf("blah[2] = %d\n", blah[2]);

    // Start monitoring memory writes
    MonitorRange((void*)&blah[1], sizeof(blah[1]));

    // Write to monitored memory
    pWriteToMonitoredMemory();

    // Stop monitoring memory writes
    MonitorRange(NULL, 0);

    printf("blah[0] = %d\n", blah[0]);
    printf("blah[1] = %d\n", blah[1]);
    printf("blah[2] = %d\n", blah[2]);
  }
  __except(ExceptionFilter(GetExceptionInformation(),
                           &WriteMonitor)) // write monitor callback function
  {
    // never executed
  }

  printf("\nstop\n");
  return 0;
}
