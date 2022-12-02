line1:
	python3 main.py 63

line2:
	python3 main.py 70

line3:
	python3 main.py 75

line4:
	python3 main.py 80

line-auto:
	python3 main.py -1

download-wlan0:
	touch tmp/1
	rm /Users/caxapok/Documents/Arduino/RTC-2022/tmp/*
	scp pi@192.168.2.65:/home/pi/Desktop/tmp/* /Users/caxapok/Documents/Arduino/RTC-2022/tmp/

download-wlan1:
	touch tmp/1
	rm /Users/caxapok/Documents/Arduino/RTC-2022/tmp/*
	scp pi@192.168.2.134:/home/pi/Desktop/tmp/* /Users/caxapok/Documents/Arduino/RTC-2022/tmp/

upload:
	rm ../tmp/*
	python3 grab_image.py

qr:
	python3 read_qr.py

install_qr:
	sudo apt-get install libzbar-dev libzbar0
	pip3 install pyzbar

