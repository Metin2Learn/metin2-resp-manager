## find:
	def __PlayMusic(self, flag, filename):
		[...]

## paste below:
	if app.ENABLE_RESP_SYSTEM:
		def BINARY_SetMobRespData(self, mobVnum, data):
			self.interface.wndResp.SetMobRespData(mobVnum, data)

		def BINARY_SetMobDropData(self, mobVnum, data):
			self.interface.wndResp.SetMobDropData(mobVnum, data)

		def BINARY_SetMapData(self, data, currentBossCount, maxBossCount, currentMetinCount, maxMetinCount):
			self.interface.wndResp.SetMapData(data, currentBossCount, maxBossCount, currentMetinCount, maxMetinCount)

		def BINARY_RefreshResp(self, id, mobVnum, time, cord):
			self.interface.wndResp.RefreshRest(id, mobVnum, time, cord)
