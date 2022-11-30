run:
	python3 main.py

update:
	git pull

download:
	echo "pi" > .password_pi
	rm /Users/caxapok/Documents/Arduino/RTC-2022/tmp/*
	scp pi@192.168.2.65:/home/pi/Desktop/tmp/* /Users/caxapok/Documents/Arduino/RTC-2022/tmp/ < .password_pi

upload:
	rm ../tmp/*
	python3 grab_image.py

qr:
	python3 read_qr.py

install_qr:
	sudo apt-get install libzbar-dev libzbar0
	pip3 install pyzbar

