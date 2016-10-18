# Tips for Raspberry Pi
## Remote Login

* RealVNC
 * [instal](https://www.realvnc.com/docs/raspberry-pi.html#raspberry-pi-legacy)
 * F8 -> Save Connection
 * Set resolution
   * sudo leafpad /boot/config.txt
   ```
   hdmi_force_hotplug=1
   hdmi_group=1
   hdmi_mode=16 # (or any other pi resolution you want, 16 is for 1080p)
   ```
 * [Optimizing the Raspberry Pi Zero / Raspberry Pi 1 for VNC](https://support.realvnc.com/Knowledgebase/Article/View/523/2/the-screen-is-too-small-when-connecting-to-a-headless-raspberry-pi-running-vnc-server-in-service-mode)
* Team Viewer
 * [install](https://www.teamviewer.com/en/download/)

## File
* WinSCP
* [Share folder with Windows](http://raspberrypihq.com/how-to-share-a-folder-with-a-windows-computer-from-a-raspberry-pi/)
