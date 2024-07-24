## find:
import localeInfo

## paste below:
if app.ENABLE_RESP_SYSTEM:
	import uiresp
	
## find:
		self.wndGuildBuilding = None

## paste below:
		if app.ENABLE_RESP_SYSTEM:
			self.wndResp = None

## find:
		self.dlgRefineNew = uiRefine.RefineDialogNew()
		self.dlgRefineNew.Hide()

## paste below:
		if app.ENABLE_RESP_SYSTEM:
			self.wndResp = uiresp.RespDialog()
			self.wndResp.Hide()

## find:
		self.privateShopBuilder.SetItemToolTip(self.tooltipItem)

## paste below:
		if app.ENABLE_RESP_SYSTEM:
			self.wndResp.SetItemToolTip(self.tooltipItem)

## find:
		if self.wndItemSelect:
			self.wndItemSelect.Destroy()

## paste below:
		if app.ENABLE_RESP_SYSTEM:
			if self.wndResp:
				self.wndResp.Destroy()

				del self.wndResp

## find:
		if self.wndExpandedTaskBar:
			self.wndExpandedTaskBar.Hide()

## paste below:
		if app.ENABLE_RESP_SYSTEM:
			if self.wndResp:
				self.wndResp.Hide()

## find:
		if self.wndExpandedTaskBar:
			hideWindows += self.wndExpandedTaskBar,

## paste below:
		if app.ENABLE_RESP_SYSTEM and self.wndResp:
			hideWindows += self.wndResp,
