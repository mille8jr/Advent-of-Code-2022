totals = {}
with open('Day 1/input.txt','r') as f:
    temp = 0
    elfID = 0
    for line in f:
        if line.strip() == "":
            elfID += 1
            totals[elfID] = temp
            temp = 0
        else:
            temp += int(line)

#Answer for part 1
# calories = 0
# for key in totals:
#     if totals[key] > calories:
#         calories = totals[key]

def sort_by_value(item):
    return item[1]

count = 0
tempTotal = 0
for k, v in sorted(totals.items(), reverse=True, key=sort_by_value):
    if count < 3:
        tempTotal += v
    count += 1

print(tempTotal)