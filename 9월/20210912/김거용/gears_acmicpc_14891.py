import sys

def rotate(gear, rotation):
    if(rotation==1):
        gear = [gear[7]]+gear;
        del(gear[8])
    elif(rotation==-1):
        gear.append(gear[0])
        del(gear[0])
    return gear

gears = [list(map(int, list(input()))) for _ in range(4)]

instructionSize = int(input())
instructions = [list(map(int, input().rstrip().split(' '))) for _ in range(instructionSize)]

for gearNum, move in instructions:
    gearRotation = [0,0,0,0]

    gearIndex = gearNum-1
    gearRotation[gearIndex] = move
    for nextGear in range(gearIndex+1,4):
        sourceGear=nextGear-1
        if(gearRotation[sourceGear]!=0 and gears[sourceGear][2] + gears[nextGear][6] == 1):
            gearRotation[nextGear] =  gearRotation[sourceGear] *-1
            
    for nextGear in range(gearIndex-1,-1, -1):
        sourceGear=nextGear-1
        if(gearRotation[sourceGear]!=0 and gears[nextGear][2] + gears[sourceGear][6] == 1):
            gearRotation[nextGear] =  gearRotation[sourceGear] *-1
    
    #print(gearRotation)
    for gearIndex in range(4):
        gears[gearIndex] = rotate(gears[gearIndex], gearRotation[gearIndex])

answer = 0;
for gearIndex in range(4):
    answer += gears[gearIndex][0] * pow(2, gearIndex)
    
print(answer)
