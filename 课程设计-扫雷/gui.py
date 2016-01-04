# coding:utf8
import wx
from game import Game

class App(wx.App):


    def OnInit(self):
        frame = Frame()
        frame.Show()
        self.SetTopWindow(frame)
        return True


class Frame(wx.Frame):

    each = 28

    length = 8
    width = 10
    mineNum = 10

    existNum = length * width - mineNum

    def __init__(self):
        wx.Frame.__init__(self, parent=None, title=u'扫雷', pos=wx.DefaultPosition,
                          size=wx.DefaultSize)
        self.panel = wx.Panel(self)
        self.SetMenu()

        self.numBmp = []
        for i in range(9):
            self.numBmp.append(wx.Bitmap('0'+str(i)+'.bmp', wx.BITMAP_TYPE_BMP))
        self.initBmp = wx.Bitmap('init.png', wx.BITMAP_TYPE_PNG)
        self.flagBmp = wx.Bitmap('flag.bmp', wx.BITMAP_TYPE_BMP)
        self.mineBmp = wx.Bitmap('mine.bmp', wx.BITMAP_TYPE_BMP)

    def SetMenu(self):

        menuBar = wx.MenuBar()

        optionMenu = wx.Menu()
        resetMenuItem = optionMenu.Append(wx.ID_ANY, u'开始/重置')
        optionMenu.AppendSeparator()
        settingMenuItem = optionMenu.Append(wx.ID_ANY, u'设置')
        optionMenu.AppendSeparator()
        exitMenuItem = optionMenu.Append(wx.ID_ANY, u'退出')
        menuBar.Append(optionMenu, u'选项')

        helpMenu = wx.Menu()
        aboutMenuItem = helpMenu.Append(wx.ID_ANY, u'关于')
        menuBar.Append(helpMenu, u'帮助')

        self.SetMenuBar(menuBar)

        self.Bind(wx.EVT_MENU, self.OnSetting, settingMenuItem)
        self.Bind(wx.EVT_MENU, self.OnReset, resetMenuItem)
        self.Bind(wx.EVT_MENU, self.OnExit, exitMenuItem)

        self.Bind(wx.EVT_MENU, self.OnAbout, aboutMenuItem)

    def OnSetting(self, event):

        self.dialog = wx.Dialog(self, title=u'设置', pos=wx.DefaultPosition, size=(95, 160))

        wx.StaticText(self.dialog, wx.ID_ANY, u'长度：', pos=(10, 15))
        self.lenText = wx.TextCtrl(self.dialog, wx.ID_ANY, str(self.length), pos=(50, 10), size=(30, 25))

        wx.StaticText(self.dialog, wx.ID_ANY, u'宽度：', pos=(10, 45))
        self.widText = wx.TextCtrl(self.dialog, wx.ID_ANY, str(self.width), pos=(50, 40), size=(30, 25))

        wx.StaticText(self.dialog, wx.ID_ANY, u'雷数：', pos=(10, 75))
        self.mineNumText = wx.TextCtrl(self.dialog, wx.ID_ANY, str(self.mineNum), pos=(50, 70), size=(30, 25))

        confirmButton = wx.Button(self.dialog, wx.ID_ANY, u'确认', pos=(10, 100), size=(70, 25))
        confirmButton.Bind(wx.EVT_BUTTON, self.OnConfirmSetting)

        self.dialog.Show()


    def OnReset(self, event):
        self.panel.Destroy()

        self.existNum = self.length * self.width - self.mineNum
        self.SetSize((self.length*self.each+17, self.width*self.each+60))
        # self.SetMaxSize((self.length*self.each+17, self.width*self.each+60))
        # self.SetMinSize((self.length*self.each+17, self.width*self.each+60))
        self.panel = wx.Panel(self, size=(self.length*self.each, self.width*self.each))
        self.mapList = []
        sizeAll = wx.BoxSizer(wx.HORIZONTAL)
        for i in range(self.length):
            self.mapList.append([])
            sizeEach = wx.BoxSizer(wx.VERTICAL)
            for j in range(self.width):
                button = wx.BitmapButton(self.panel, i*self.width+j, pos=(i*self.each, j*self.each),
                                         size=(self.each, self.each), style=wx.BU_AUTODRAW)
                button.Bind(wx.EVT_LEFT_DOWN, self.OnLeftClick)
                button.Bind(wx.EVT_RIGHT_DOWN, self.OnRightClick)
                self.mapList[i].append(button)
                sizeEach.Add(button)
            sizeAll.Add(sizeEach)
        self.panel.SetSizer(sizeAll)
        self.StartGame()

    def StartGame(self):
        game = Game(self.length, self.width, self.mineNum)
        self.mapCoord = game.mapCoord


    def OnLeftClick(self, event):
        id = event.GetId()
        x = id / self.width + 1
        y = id % self.width + 1
        button = self.panel.FindWindowById(id)
        button.SetFocus()
        if not self.mapCoord[x][y].flag and not self.mapCoord[x][y].openMark:
            if self.mapCoord[x][y].mineNum == -1:
                self.gameLost()
            elif self.mapCoord[x][y].mineNum == 0:
                self.breathFirstSearch(x, y)
            else:
                self.mapCoord[x][y].openMark = True
                self.existNum -= 1
                button.SetBitmap(self.numBmp[self.mapCoord[x][y].mineNum])
            if not self.existNum:
                self.gameWin()

    def OnRightClick(self, event):
        id = event.GetId()
        x = id / self.width + 1
        y = id % self.width + 1
        button = self.panel.FindWindowById(id)
        button.SetFocus()
        if not self.mapCoord[x][y].openMark:
            if self.mapCoord[x][y].flag:
                button.SetBitmap(self.initBmp)
                self.mapCoord[x][y].flag = False
            else:
                button.SetBitmap(self.flagBmp)
                self.mapCoord[x][y].flag = True


    def OnExit(self, event):
        self.Close()

    def OnAbout(self, event):
        wx.MessageBox(u'\n制作人：王必聪 宋源栋 谭学昱 刘鑫禹\n')

    def OnConfirmSetting(self, event):
        self.length = int(self.lenText.GetValue())
        self.width = int(self.widText.GetValue())
        self.mineNum = int(self.mineNumText.GetValue())
        self.OnReset(event)
        self.dialog.Close()

    def gameLost(self):
        self.showMap()
        wx.MessageBox(u'你失败了！')

    def gameWin(self):
        self.showMap()
        wx.MessageBox(u'你胜利了！')

    def showMap(self):
        mapList = self.mapList
        mapCoord = self.mapCoord
        for i in range(1, self.length+1):
            for j in range(1, self.width+1):
                if not mapCoord[i][j].openMark:
                    mapCoord[i][j].openMark = True
                    if mapCoord[i][j].mineNum >= 0:
                        mapList[i-1][j-1].SetBitmap(self.numBmp[mapCoord[i][j].mineNum])
                    else:
                        mapList[i-1][j-1].SetBitmap(self.mineBmp)


    def breathFirstSearch(self, x, y):
        if not self.mapCoord[x][y].openMark:
            self.mapCoord[x][y].openMark = True
            self.existNum -= 1
            self.mapList[x-1][y-1].SetBitmap(self.numBmp[self.mapCoord[x][y].mineNum])
            if not self.mapCoord[x][y].mineNum:
                self.breathFirstSearch(x+1, y)
                self.breathFirstSearch(x-1, y)
                self.breathFirstSearch(x, y+1)
                self.breathFirstSearch(x, y-1)

                self.breathFirstSearch(x+1, y+1)
                self.breathFirstSearch(x-1, y+1)
                self.breathFirstSearch(x+1, y-1)
                self.breathFirstSearch(x-1, y-1)


def main():
    app = App()
    app.MainLoop()

if __name__ == '__main__':
    main()