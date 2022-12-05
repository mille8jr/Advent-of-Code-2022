TotalScore = 0

def whatToThrow(player1, expectedOutcome):
    if expectedOutcome == "X":
        if player1 == "A":
            throw = "Z"
        elif player1 == "B":
            throw = "X"
        else: throw = "Y"
    elif expectedOutcome == "Y":
        if player1 == "A":
            throw = "X"
        elif player1 == "B":
            throw = "Y"
        else: throw = "Z"
    elif expectedOutcome == "Z":
        if player1 == "A":
            throw = "Y"
        elif player1 == "B":
            throw = "Z"
        else: throw = "X"
    return throw

with open('Day 2/input.txt','r') as f:
    for round in f.readlines():
        move = round.split(' ')
        player1 = move[0].strip()
        player2 = move[1].strip()

        #Check what player2 threw based on inputs and assign base round points
        if whatToThrow(player1, player2) == "X":
            roundPoints = 1
        elif whatToThrow(player1, player2) == "Y":
            roundPoints = 2
        elif whatToThrow(player1, player2) == "Z":
            roundPoints = 3
        else:
            print("error")


        #Check how the round should end
        if player2 == "Y":
            roundPoints += 3
        elif player2 == "Z":
            roundPoints += 6

        
        TotalScore += roundPoints
print(TotalScore)