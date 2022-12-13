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

download:
	touch ./tmp/1
	rm ./tmp/*
	scp pi@192.168.2.121:/home/pi/Desktop/tmp/* ./tmp/

upload:
	rm ../tmp/*
	python3 grab_image.py

qr:
	python3 read_qr.py

install_qr:
	sudo apt-get install libzbar-dev libzbar0
	pip3 install pyzbar

