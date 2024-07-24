## search for:
	def SetText(self, text, height = 0):
		if not self.ButtonText:
			textLine = TextLine()
			textLine.SetParent(self)
			textLine.SetPosition(self.GetWidth() / 2, self.GetHeight() / 2 + height)
			textLine.SetVerticalAlignCenter()
			textLine.SetHorizontalAlignCenter()
			textLine.Show()
			self.ButtonText = textLine

		self.ButtonText.SetText(text)

## replace with:
	if app.ENABLE_RESP_SYSTEM:
		def __CreateTextLine(self, height=0):
			if not self.ButtonText:
				textLine = TextLine()
				textLine.SetParent(self)
				textLine.SetPosition(self.GetWidth() / 2, self.GetHeight() / 2 + height)
				textLine.SetVerticalAlignCenter()
				textLine.SetHorizontalAlignCenter()
				textLine.Show()
				self.ButtonText = textLine

		def SetTextColor(self, color):
			self.__CreateTextLine()
			self.ButtonText.SetPackedFontColor(color)

		def SetOutline(self, flag):
			self.__CreateTextLine()
			self.ButtonText.SetOutline(flag)

		def SetFontName(self, fontname):
			self.__CreateTextLine()
			self.ButtonText.SetFontName(fontname)

		def SetText(self, text, height=0):
			self.__CreateTextLine(height)
			self.ButtonText.SetText(text)

	else:
		def SetText(self, text, height = 0):
			if not self.ButtonText:
				textLine = TextLine()
				textLine.SetParent(self)
				textLine.SetPosition(self.GetWidth() / 2, self.GetHeight() / 2 + height)
				textLine.SetVerticalAlignCenter()
				textLine.SetHorizontalAlignCenter()
				textLine.Show()
				self.ButtonText = textLine

			self.ButtonText.SetText(text)

## search for:
class ScriptWindow(Window):
	[...]

## paste below:
if app.ENABLE_RESP_SYSTEM:
	class RespBoard(Window):
		CORNER_WIDTH = 16
		CORNER_HEIGHT = 16
		LINE_WIDTH = 16
		LINE_HEIGHT = 16
		BOARD_COLOR = grp.GenerateColor(0.03, 0.03, 0.03, 0.44)

		LT = 0
		LB = 1
		RT = 2
		RB = 3
		L = 0
		R = 1
		T = 2
		B = 3

		def __init__(self, layer="UI"):
			Window.__init__(self, layer)

			CornerFileNames = ["d:/ymir work/ui/game/resp/board/corner_" + dir + ".tga" for dir in
							   ["lefttop", "leftbottom", "righttop", "rightbottom"]]
			LineFileNames = ["d:/ymir work/ui/game/resp/board/Line_" + dir + ".tga" for dir in
							 ["left", "right", "top", "bottom"]]

			self.Corners = []
			for fileName in CornerFileNames:
				Corner = ExpandedImageBox()
				Corner.AddFlag("attach")
				Corner.AddFlag("not_pick")
				Corner.LoadImage(fileName)
				Corner.SetParent(self)
				Corner.SetPosition(0, 0)
				Corner.Show()
				self.Corners.append(Corner)

			self.Lines = []
			for fileName in LineFileNames:
				Line = ExpandedImageBox()
				Line.AddFlag("attach")
				Line.AddFlag("not_pick")
				Line.LoadImage(fileName)
				Line.SetParent(self)
				Line.SetPosition(0, 0)
				Line.Show()
				self.Lines.append(Line)

			Base = Bar()
			Base.SetParent(self)
			Base.AddFlag("attach")
			Base.AddFlag("not_pick")
			Base.SetPosition(self.CORNER_WIDTH, self.CORNER_HEIGHT)
			Base.SetColor(self.BOARD_COLOR)
			Base.Show()
			self.Base = Base

			self.Lines[self.L].SetPosition(0, self.CORNER_HEIGHT)
			self.Lines[self.T].SetPosition(self.CORNER_WIDTH, 0)

		def __del__(self):
			Window.__del__(self)

		def SetSize(self, width, height):

			width = max(self.CORNER_WIDTH * 2, width)
			height = max(self.CORNER_HEIGHT * 2, height)
			Window.SetSize(self, width, height)

			self.Corners[self.LB].SetPosition(0, height - self.CORNER_HEIGHT)
			self.Corners[self.RT].SetPosition(width - self.CORNER_WIDTH, 0)
			self.Corners[self.RB].SetPosition(width - self.CORNER_WIDTH, height - self.CORNER_HEIGHT)
			self.Lines[self.R].SetPosition(width - self.CORNER_WIDTH, self.CORNER_HEIGHT)
			self.Lines[self.B].SetPosition(self.CORNER_HEIGHT, height - self.CORNER_HEIGHT)

			verticalShowingPercentage = float((height - self.CORNER_HEIGHT * 2) - self.LINE_HEIGHT) / self.LINE_HEIGHT
			horizontalShowingPercentage = float((width - self.CORNER_WIDTH * 2) - self.LINE_WIDTH) / self.LINE_WIDTH
			self.Lines[self.L].SetRenderingRect(0, 0, 0, verticalShowingPercentage)
			self.Lines[self.R].SetRenderingRect(0, 0, 0, verticalShowingPercentage)
			self.Lines[self.T].SetRenderingRect(0, 0, horizontalShowingPercentage, 0)
			self.Lines[self.B].SetRenderingRect(0, 0, horizontalShowingPercentage, 0)
			self.Base.SetSize(width - self.CORNER_WIDTH * 2, height - self.CORNER_HEIGHT * 2)

		def ShowInternal(self):
			self.Base.Show()
			for wnd in self.Lines:
				wnd.Show()
			for wnd in self.Corners:
				wnd.Show()

		def HideInternal(self):
			self.Base.Hide()
			for wnd in self.Lines:
				wnd.Hide()
			for wnd in self.Corners:
				wnd.Hide()

	class RespCheckBox(ImageBox):
		def __init__(self):
			ImageBox.__init__(self)

			self.LoadImage("d:/ymir work/ui/game/resp/checkbox_empty.sub")

			image = MakeImageBox(self, "d:/ymir work/ui/game/resp/checkbox_full.sub", 0, 0)
			image.AddFlag("not_pick")
			image.Hide()

			self.image = image
			self.event = None
			self.uncheckEvent = None
			self.flag = False

			self.Show()

			self.SetCheck(False)

		def __del__(self):
			ImageBox.__del__(self)

		def IsChecked(self):
			return self.flag

		def SetCheck(self, flag):
			if flag:
				self.image.Show()
			else:
				self.image.Hide()
			self.flag = flag

		def SetEvent(self, event):
			self.event = event

		def SetUncheckEvent(self, event):
			self.uncheckEvent = event

		def OnMouseOverIn(self):
			if not self.flag:
				self.image.Show()

		def OnMouseOverOut(self):
			if self.flag:
				self.image.Show()
			else:
				self.image.Hide()

		def OnMouseLeftButtonUp(self):
			if self.IsChecked():
				self.SetCheck(False)
				if self.uncheckEvent:
					self.uncheckEvent()
			else:
				self.SetCheck(True)
				if self.event:
					self.event()

## search for:
			elif Type == "listboxex":
				parent.Children[Index] = ListBoxEx()
				parent.Children[Index].SetParent(parent)
				self.LoadElementListBoxEx(parent.Children[Index], ElementValue, parent)

## paste below:
			elif app.ENABLE_RESP_SYSTEM and Type == "resp_board":
				parent.Children[Index] = RespBoard()
				parent.Children[Index].SetParent(parent)
				self.LoadElementBoard(parent.Children[Index], ElementValue, parent)

			elif app.ENABLE_RESP_SYSTEM and Type == "resp_checkbox":
				parent.Children[Index] = RespCheckBox()
				parent.Children[Index].SetParent(parent)
				self.LoadElementWindow(parent.Children[Index], ElementValue, parent)

## search for:
		if True == value.has_key("text"):
			if True == value.has_key("text_height"):
				window.SetText(value["text"], value["text_height"])
			else:
				window.SetText(value["text"])

## replace with:
		if True == value.has_key("text"):
			if app.ENABLE_RESP_SYSTEM:
				if value.has_key("fontname"):
					window.SetFontName(value["fontname"])
			if True == value.has_key("text_height"):
				window.SetText(value["text"], value["text_height"])
			else:
				window.SetText(value["text"])

			if app.ENABLE_RESP_SYSTEM:
				if value.has_key("text_color"):
					window.SetTextColor(value["text_color"])

				if value.has_key("outline"):
					window.SetOutline(value["outline"])
