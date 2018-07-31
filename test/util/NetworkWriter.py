import struct

class NetworkWriter:

	def __init__(self, data = b''):
		self._data = data

	def getData(self):
		return self._data

	def getSize(self):
		return len(self._data)

	def addRaw(self, data):
		self._data += data

	def addSize(self, size):
		self.addRaw(struct.pack('<I', size))

	def addString(self, string):
		self.addSize(len(string))
		self.addRaw(str.encode(string))

	def addInt8(self, int8):
		self.addRaw(struct.pack('<b', int8))

	def addUint8(self, uint8):
		self.addRaw(struct.pack('<B', uint8))