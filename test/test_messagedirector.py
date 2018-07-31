import unittest

from util.NetworkConnector import NetworkConnector
from util.NetworkReader import NetworkReader
from util.NetworkWriter import NetworkWriter

class MessageDirectorTest(unittest.TestCase):

	@classmethod
	def setUpClass(cls):
		cls.socket = NetworkConnector()

	@classmethod
	def tearDownClass(cls):
		cls.socket.close()
		cls.socket = None

	def test_md_hello(self):
		self.socket.connect("127.0.0.1", 7199)

	def test_md_send(self):
		nw = NetworkWriter()
		nw.addInt8(126)
		self.socket.send(nw)

if __name__ == '__main__':
	unittest.main()