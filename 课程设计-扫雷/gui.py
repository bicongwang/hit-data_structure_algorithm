# coding:utf8
import wx

class App(wx.App):


    def OnInit(self):
        frame = Frame()
        frame.Show()
        return True


class Frame(wx.Frame):

    each = 25

    length = 10
    width = 10
    mineNum = 10

    def __init__(self):
        wx.Frame.__init__(self, title=u'扫雷', parent=None, pos=(400, 200),
                          size=(self.length*self.each, self.width*self.each))
        self.panel = wx.Panel(self)
        self.SetMenu()

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

        self.dialog = wx.Dialog(self, title=u'设置', pos=(500, 250), size=(100, 160))

        wx.StaticText(self.dialog, -1, u'长度：', pos=(10, 15))
        self.lenText = wx.TextCtrl(self.dialog, -1, str(self.length), pos=(50, 10), size=(30, 25))

        wx.StaticText(self.dialog, -1, u'宽度：', pos=(10, 45))
        self.widText = wx.TextCtrl(self.dialog, -1, str(self.width), pos=(50, 40), size=(30, 25))

        wx.StaticText(self.dialog, -1, u'雷数：', pos=(10, 75))
        self.mineNumText = wx.TextCtrl(self.dialog, -1, str(self.mineNum), pos=(50, 70), size=(30, 25))

        confirmButton = wx.Button(self.dialog, -1, u'确认', pos=(10, 100), size=(70, 25))
        confirmButton.Bind(wx.EVT_BUTTON, self.OnConfirmSetting)

        self.dialog.Show()

    def OnConfirmSetting(self, event):
        self.length = int(self.lenText.GetValue())
        self.width = int(self.widText.GetValue())
        self.mineNum = int(self.mineNumText.GetValue())
        self.OnReset(event)
        self.dialog.Close()

    def OnReset(self, event):
        self.panel.Destroy()
        self.SetSize((self.length*self.each+7, self.width*self.each+50))
        self.panel = wx.Panel(self, size=(self.length*self.each, self.width*self.each))
        mapList = []
        for i in range(self.length):
            mapList.append([])
            for j in range(self.width):
                button = wx.BitmapButton(self.panel, -1, pos=(i*(self.each-1), j*(self.each-1)),
                                         size=(self.each, self.each), style=wx.BU_AUTODRAW)
                mapList[i].append(button)


    def OnExit(self, event):
        self.Close()

    def OnAbout(self, event):
        wx.MessageBox(u'\n制作人：王必聪\n')

def main():
    app = App()
    app.MainLoop()

if __name__ == '__main__':
    main()