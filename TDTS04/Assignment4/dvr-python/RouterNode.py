#!/usr/bin/env python
import GuiTextArea, RouterPacket, F
from copy import deepcopy

class RouterNode():
    myID = None
    myGUI = None
    sim = None
    costs = None
    

    # Access simulator variables with:
    # self.sim.POISONREVERSE, self.sim.NUM_NODES, etc.

    # --------------------------------------------------
    def __init__(self, ID, sim, costs):
        self.myID = ID
        self.sim = sim
        self.myGUI = GuiTextArea.GuiTextArea("  Output window for Router #" + str(ID) + "  ")
        self.costs = deepcopy(costs)
        
        self.neighCosts = deepcopy(sim.connectcosts)
        self.minCosts = deepcopy(costs)
        self.nextHops = []

        self.initRouteTable(self.costs)
        self.propagate()

    # --------------------------------------------------
    def initRouteTable(self, costs):
        for i in range(self.sim.NUM_NODES):
            for j in range(self.sim.NUM_NODES):
                self.neighCosts[i][j] = self.sim.INFINITY if i != j else 0
            
        
        n = 0
        for i in costs:
            if i != self.sim.INFINITY and i != 0:
                self.nextHops.append(n)
            else:
                self.nextHops.append(self.myID)
            n += 1

    # --------------------------------------------------
    def propagate(self):
        pCosts = deepcopy(self.minCosts)
        for i in range(self.sim.NUM_NODES):
            if self.costs[i] != 0 and self.costs[i] != self.sim.INFINITY: # om direkt granne
                if self.sim.POISONREVERSE:
                    for j in range(self.sim.NUM_NODES):
                        if self.nextHops[j] == i and i != j:
                            pCosts[j] = self.sim.INFINITY
                pkt = RouterPacket.RouterPacket(self.myID, i, pCosts)
                self.sendUpdate(pkt)

    # --------------------------------------------------
    def recvUpdate(self, pkt):
        #self.myGUI.println(f"Received update from {pkt.sourceid} with table {pkt.mincost}")
        changed_table = False

        for i in range(self.sim.NUM_NODES):
            if self.neighCosts[pkt.sourceid][i] != pkt.mincost[i]:
                changed_table = True
                self.neighCosts[pkt.sourceid][i] = pkt.mincost[i]

        if changed_table:
            for i in range(self.sim.NUM_NODES):
                bestCost = self.sim.INFINITY
                bestHop = self.myID

                for j in range(self.sim.NUM_NODES):
                    if self.costs[j] != self.sim.INFINITY:
                        newCost = self.costs[j] + self.neighCosts[j][i]
                        if newCost < bestCost:
                            bestCost = newCost
                            bestHop = j

                if bestCost != self.minCosts[i]:
                    self.minCosts[i] = bestCost
                    self.nextHops[i] = bestHop

            self.propagate()

    # --------------------------------------------------
    def sendUpdate(self, pkt):
        self.sim.toLayer2(pkt)


    # --------------------------------------------------
    def printDistanceTable(self):
        self.myGUI.println("Current table for " + str(self.myID) + '\n' +
                           "Distancetable:" + '\n' + "  cost  |" +
                           '\t' + str(self.minCosts) + '\n' +
                           "  route |" + '\t' + str(self.nextHops) + '\n')
    # --------------------------------------------------
    def updateLinkCost(self, dest, newcost):
        self.myGUI.println(f"Updated link cost to {dest}: {newcost}")

        self.costs[dest] = newcost
        self.minCosts[dest] = self.sim.INFINITY

        
        self.propagate()
