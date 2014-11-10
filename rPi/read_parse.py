import ParsePy
import serial
import time
ser = serial.Serial(port="/dev/serial/by-id/usb-Arduino__www.arduino.cc__0043_75331313133351309092-if00", baudrate=9600)
#ser = serial.Serial(port="/dev/tty.usbmodem1421", baudrate=9600)
ser.flushInput()
ser.flushOutput()

ParsePy.APPLICATION_ID = "yC0kRgQVWDOjKZfvWtJrITDbzdDmEEqg6WKrjXoc"
ParsePy.MASTER_KEY = "fkTsokkBKrzOCuzqizVd9EE1SNYgplmluNsENLtZ"

time.sleep(2)
last_command = -1
while 1:
	try:
		ser.write('a')
		time.sleep(.01)
		try:
			sensor_reading = int(ser.read(ser.inWaiting()))
		except:
			while sensor_reading == '':
				ser.write('a')
				time.sleep(.01)
				sensor_reading = int(ser.read(ser.inWaiting()))
		print sensor_reading

		light_status = ParsePy.ParseObject("LightStatus")
		light_status.value = sensor_reading
		light_status.save()

		query = ParsePy.ParseQuery("LightCommand").limit(1).order("createdAt", decending=True)
		light_command = query.fetch()[0]
		if ((light_command.command == 0 and last_command == 1) or last_command == -1):
			ser.write('0')
			print light_command.command
			time.sleep(.1)
			last_command = 0
		elif (light_command.command == 1 and last_command == 0):
			ser.write('1')
			print light_command.command
			time.sleep(.1)
			last_command = 1

		ser.flushInput()
		ser.flushOutput()

	except KeyboardInterrupt:
		ser.flushInput()
		ser.flushOutput()
		ser.close()

