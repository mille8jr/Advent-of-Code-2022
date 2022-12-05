TotalScore = 0
with open('Day 2/input.txt','r') as f:
    for round in f.readlines():
        move = round.split(' ')
        player1 = move[0].strip()
        player2 = move[1].strip()

        #Check what was thrown for base round points
        if player2 == "X":
            roundPoints = 1
        elif player2 == "Y":
            roundPoints = 2
        elif player2 == "Z":
            roundPoints = 3
        else:
            print("error")


        #Check who won the round and provide points
        if player1 == "A":
            if player2 == "Y":
                roundPoints += 6
            elif player2 == "X":
                roundPoints += 3
        elif player1 == "B":
            if player2 == "Z":
                roundPoints += 6
            elif player2 == "Y":
                roundPoints += 3
        elif player1 == "C":
            if player2 == "X":
                roundPoints += 6
            elif player2 == "Z":
                roundPoints += 3
        else:
            print("error")

        TotalScore += roundPoints
print(TotalScore)