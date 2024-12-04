if __name__ == "__main__":
    list1 = []
    list2map = {}

    nums = open("day01-data.txt", "r")
    for line in nums:
        if line == "\n":
            continue
        list1.append(int(line[:5]))
        secondnum = int(line[8:13])
        if secondnum in list2map:
            list2map[secondnum] += 1
            continue
        list2map[secondnum] = 1

    similarity = 0
    for num in list1:
        similarity += num * list2map.get(num, 0)
    print(similarity)
