# coding:utf8
from random import randint

class game(object):

    def __init__(self, length=10, width=10, mineNum=10):
        self.length = length
        self.width = width
        self.mineNum = mineNum
        self.mapCoord = [[Box()] * (width + 2)] * (length + 2)

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
        for i in range(1, self.length + 1):
            for j in range(1, self.width + 1):
                self.calculateMineNum(i, j)


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


class Box(object):

    def __init__(self, mineNum=0, flag=False, openMark = False):
        self.mineNum = mineNum
        self.flag = flag
        self.openMark = openMark
