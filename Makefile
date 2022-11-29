run:
	python3 main.py

update:
	git pull

download:
	echo "pi" > .password_pi
	rm /Users/caxapok/Documents/Arduino/RTC-2022/tmp/*
	scp pi@192.168.2.65:/home/pi/Desktop/tmp/* /Users/caxapok/Documents/Arduino/RTC-2022/tmp/ < .password_pi
