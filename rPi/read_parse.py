import ParsePy
import serial
import time
ser = serial.Serial(port="/dev/tty.usbmodem1421", baudrate=9600)
ser.flushInput()
ser.flushOutput()

ParsePy.APPLICATION_ID = "yC0kRgQVWDOjKZfvWtJrITDbzdDmEEqg6WKrjXoc"
ParsePy.MASTER_KEY = "fkTsokkBKrzOCuzqizVd9EE1SNYgplmluNsENLtZ"

time.sleep(2)

ser.write('a')
time.sleep(.1)
sensor_reading = int(ser.read(ser.inWaiting()))

light_status = ParsePy.ParseObject("LightStatus")
light_status.value = sensor_reading
light_status.save()

query = ParsePy.ParseQuery("lightCommand").limit(1).order("createdAt", decending=True)
light_command = query.fetch()[0]

print light_command.command