# coding:utf8
from random import randint

class Game(object):

    def __init__(self, length=8, width=10, mineNum=10):
        self.length = length
        self.width = width
        self.mineNum = mineNum
        self.mapCoord = []
        # 初始化Box二维列表
        for i in range(length+2):
            self.mapCoord.append([])
            for j in range(width+2):
                self.mapCoord[i].append(Box())
        self.createMap()

    def createMap(self):
        existMineCoords = []
        i = 0
        while i < self.mineNum:
            x = randint(1, self.length)
            y = randint(1, self.width)
            if (x, y) not in existMineCoords:
                existMineCoords.append((x, y))
                i += 1
        for (x, y) in existMineCoords:
            self.mapCoord[x][y].mineNum = -1
        # 布置地雷
        for i in range(1, self.length + 1):
            for j in range(1, self.width + 1):
                self.calculateMineNum(i, j)
        for i in range(0,self.length + 2):
            for j in range(0, self.width + 2):
                if i == 0 or j == 0 or i == self.length + 1 or j == self.width + 1:
                    self.mapCoord[i][j].openMark = True
        # 令外圈为打开状态


    def calculateMineNum(self, x, y):
        if self.mapCoord[x][y].mineNum == -1:
            return
        count = 0
        if self.mapCoord[x+1][y].mineNum == -1:
            count += 1
        if self.mapCoord[x-1][y].mineNum == -1:
            count += 1
        if self.mapCoord[x][y+1].mineNum == -1:
            count += 1
        if self.mapCoord[x][y-1].mineNum == -1:
            count += 1
        if self.mapCoord[x+1][y+1].mineNum == -1:
            count += 1
        if self.mapCoord[x-1][y+1].mineNum == -1:
            count += 1
        if self.mapCoord[x+1][y-1].mineNum == -1:
            count += 1
        if self.mapCoord[x-1][y-1].mineNum == -1:
            count += 1
        self.mapCoord[x][y].mineNum = count

# 代表每一个格子的状态
class Box(object):

    def __init__(self, mineNum=0, flag=False, openMark = False):
        self.mineNum = mineNum
        self.flag = flag
        self.openMark = openMark

# 测试该模板的运行情况
if __name__ == '__main__':
    game = Game()
    mapCoord = game.mapCoord
    for i in range(len(mapCoord)):
        for j in range(len(mapCoord[0])):
            print mapCoord[i][j].mineNum,
        print
    print len(mapCoord), len(mapCoord[0])