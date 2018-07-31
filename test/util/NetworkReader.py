import struct

class NetworkReader:

	def __init__(self, data, index = 0):
		self._data = data
		self._index = index

	def readInt8(self):
		# TODO: Overflow check here
		if self._index > len(self._data):
			print("End of buffer")
			return

		# Calculate 'theoretical' size of an int8
		size = struct.calcsize('<b')

		self._index += size
		
		data = struct.unpack('<b', self._data[self._index - size : self._index])[0]