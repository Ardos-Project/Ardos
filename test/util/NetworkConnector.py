import struct
from util.NetworkReader import NetworkReader
from socket import socket, AF_INET, SOCK_STREAM, SOL_TCP, TCP_NODELAY

class NetworkConnector:

	def __init__(self):
		self.sock = socket(AF_INET, SOCK_STREAM)
		self.sock.settimeout(0.1)
		
		# Disable Nagle's algorithm.
		self.sock.setsockopt(SOL_TCP, TCP_NODELAY, 1)

	def connect(self, ip, port):
		self.sock.connect((ip, port))

	def close(self):
		self.sock.close()

	def send(self, writer):
		packet = writer.getData()
		self.sock.send(packet)

	def handlePacket(self, packet, handler):
		reader = self.read()
		if reader is None:
			return

		msg = reader.readUint16()
		if msg != packet:
			return
			
		handler(reader)

	def read(self):
		response = self.sock.recv(1024)
		reader = NetworkReader(response)
		return reader