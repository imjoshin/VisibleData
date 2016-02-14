import sys, serial, time
arduino = serial.Serial("/dev/ttyACM0", 9600, timeout=5)
lastInit = time.time()

print "Reading from %s" % (arduino.name)
while True:
	if time.time() - lastInit > 20:
		lastInit = time.time()
		arduino.close()
		arduino = serial.Serial("/dev/ttyACM0", 9600, timeout=5)
	data = arduino.readline()
	if data:
		sys.stdout.write(data)
		sys.stdout.flush()

