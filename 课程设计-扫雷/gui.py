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

    each = 28  # 每个格子所在矩阵的像素边长

    length = 8
    width = 10
    mineNum = 10
    time = 0

    existClosedNum = length * width - mineNum  # 为了判断胜利条件
    existMineNum = mineNum

    def __init__(self):
        wx.Frame.__init__(self, parent=None, title=u'扫雷', pos=wx.DefaultPosition,
                          size=(515, 580))

        icon = wx.Icon('mine.ico', wx.BITMAP_TYPE_ICO)
        self.SetIcon(icon)

        self.statusBar = self.CreateStatusBar()
        self.statusBar.SetFieldsCount(2)
        self.statusBar.SetStatusWidths([-1, -1])
        self.statusBar.SetStatusText(u"Mine Sweeping", 0)
        self.statusBar.SetStatusText(u"By wxPython", 1)

        self.panel = wx.Panel(self)
        theme = wx.Image('theme.bmp', wx.BITMAP_TYPE_BMP)
        wx.StaticBitmap(self.panel, wx.ID_ANY, wx.BitmapFromImage(theme))
        self.SetMenu()

        # 定义所有本程序使用到的图像
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

    # 放置所有的Button
    def OnReset(self, event):

        self.panel.Destroy()
        self.timer = wx.Timer(self)
        self.timer.Start(1000)
        self.Bind(wx.EVT_TIMER, self.OnTimer, self.timer)
        self.existClosedNum = self.length * self.width - self.mineNum
        self.existMineNum = self.mineNum
        self.time = 0
        self.statusBar.SetStatusText(u"已用时间：" + str(self.time), 0)
        self.statusBar.SetStatusText(u"剩余雷数：" + str(self.existMineNum), 1)
        self.SetSize((self.length*self.each+17, self.width*self.each+84))
        # self.SetMaxSize((self.length*self.each+17, self.width*self.each+84))
        # self.SetMinSize((self.length*self.each+17, self.width*self.each+84))
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
        
    def OnTimer(self, event):
        self.time += 1
        self.statusBar.SetStatusText(u"已用时间：" + str(self.time), 0)

    def OnLeftClick(self, event):
        id = event.GetId()
        x = id / self.width + 1
        y = id % self.width + 1
        button = self.panel.FindWindowById(id)
        button.SetFocus()
        # 根据格子的属性进行不同的处理
        if not self.mapCoord[x][y].flag and not self.mapCoord[x][y].openMark:
            if self.mapCoord[x][y].mineNum == -1:
                self.gameLost() #游戏结束
            elif self.mapCoord[x][y].mineNum == 0:
                self.breathFirstSearch(x, y)  #广度优先搜索
            else:
                self.mapCoord[x][y].openMark = True
                self.existClosedNum -= 1
                button.SetBitmap(self.numBmp[self.mapCoord[x][y].mineNum])
            if not self.existClosedNum:
                self.gameWin() #游戏胜利

    def OnRightClick(self, event):
        id = event.GetId()
        x = id / self.width + 1
        y = id % self.width + 1
        button = self.panel.FindWindowById(id)
        button.SetFocus()
        # 改变标记状态
        if not self.mapCoord[x][y].openMark:
            if self.mapCoord[x][y].flag:
                button.SetBitmap(self.initBmp)
                self.existMineNum += 1
                self.statusBar.SetStatusText(u"剩余雷数：" + str(self.existMineNum), 1)
                self.mapCoord[x][y].flag = False
            else:
                button.SetBitmap(self.flagBmp)
                self.existMineNum -= 1
                self.statusBar.SetStatusText(u"剩余雷数：" + str(self.existMineNum), 1)
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
        self.timer.Stop()
        self.showMap()
        wx.MessageBox(u'你失败了！')

    def gameWin(self):
        self.timer.Stop()
        self.showMap()
        wx.MessageBox(u'你胜利了！')

    # 显示所有格子
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


    # 广度优先搜索，（实际中使用了深度优先搜索，效果一样，如果按照广度优先搜索进行，则需要利用到队列，将周围未开启的格子全部入队，出队时重复该操作）
    def breathFirstSearch(self, x, y):
        if not self.mapCoord[x][y].openMark:
            if self.mapCoord[x][y].flag:
                self.existMineNum += 1
                self.statusBar.SetStatusText(u"剩余雷数：" + str(self.existMineNum), 1)
            self.mapCoord[x][y].openMark = True
            self.existClosedNum -= 1
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