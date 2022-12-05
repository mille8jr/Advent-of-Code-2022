count = 0
with open('Day 4/input.txt','r') as f:
    for line in f:
        elfPair = line.split(',')
        elf1 = elfPair[0]
        elf1Range = elf1.split('-')
        elf1Min = int(elf1Range[0])
        elf1Max = int(elf1Range[1])

        elf2 = elfPair[1]
        elf2Range = elf2.split('-')
        elf2Min = int(elf2Range[0])
        elf2Max = int(elf2Range[1])

        if elf1Min >= elf2Min and elf1Min <= elf2Max:
            count += 1
            #print(elf1Min," > ",elf2Min,", and ",elf2Max," > ",elf1Max)
        elif elf2Min >= elf1Min and elf2Min <= elf1Max:
            count += 1
            #print(elf2Min," > ",elf1Min,", and ",elf1Max," > ",elf2Max)
print(count)

