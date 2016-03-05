# Software needed
* FFmpeg
* python 2.7.x

# Install Libraries
* pip install PIL

# How to Convert
%> ffmpeg -i "videoname.mp4" -vcodec png ./img-%04d.png
%> sh ./AllConvert.sh


# SD card directory structure
* ~/AAA/
	* img-0000.bin
	* img-0001.bin
	* img-0002.bin
	* ...
* ~/BBB/
	* img-0000.bin
	* img-0001.bin
	* img-0002.bin
	* ...