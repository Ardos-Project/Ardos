import unittest

from util.ParticipantTypes import ParticipantTypes
from util.MsgTypes import MsgTypes
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

	# Make sure we can generate a unique PID.
	def test_md_generate_pid(self):
		nw = NetworkWriter()
		nw.addUint16(ParticipantTypes["MESSAGE_DIRECTOR_PID"])
		nw.addUint16(MsgTypes["MESSAGE_DIRECTOR_GENERATE_PID"])
		self.socket.send(nw)

		self.socket.handlePacket(MsgTypes["MESSAGE_DIRECTOR_GENERATE_PID_RESP"], self.handleGeneratePidResp)

	# Make sure we can subscribe to the PID we received.
	def handleGeneratePidResp(self, reader):
		pid = reader.readUint16()

		print("PID: %s" % pid)

		nw = NetworkWriter()
		nw.addUint16(ParticipantTypes["MESSAGE_DIRECTOR_PID"])
		nw.addUint16(MsgTypes["MESSAGE_DIRECTOR_SUBSCRIBE_PID"])
		nw.addUint16(pid)
		self.socket.send(nw)

if __name__ == '__main__':
	unittest.main()