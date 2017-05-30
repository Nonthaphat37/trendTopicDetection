from bs4 import BeautifulSoup
import subprocess
import os
import re
import csv

rootdir = '/Users/nonthaphat/Research/SeniorProject/bot/pantip/'
currdir = '/Users/nonthaphat/Research/SeniorProject/new/extractPastTrend1/'
testdir = '/Users/nonthaphat/Research/SeniorProject/bot/pantip/tester/'

for subdir, dirs, files in os.walk(rootdir):
	# create new dir
	dirlast = subdir.split('/')[-1]
	if dirlast == "":
		continue;
	datedir = subdir.split('/')[-1]
	command = 'mkdir ' + currdir + dirlast
	subprocess.Popen(command, stdout=subprocess.PIPE, shell=True).communicate()

	print "add " + dirlast
	for file in files:
		pathfile = os.path.join(subdir, file)
		f = open(pathfile, 'r')
		data = f.read()
		f.close()

		soup = BeautifulSoup(data, "lxml")
		if file == 'main.html':
			soup = soup.find(id = 'item_pantip-trending')
		else:
			soup = soup.find(id = 'item_pantip-trending_room')
		soup = soup.find_all('a')

		ans = []
		for i in soup:
			topic = i.get('href')
			if topic.startswith('/topic/'):
				topic = topic.split('/')[-1]
				ans.append(topic)

		ans = '\n'.join(ans)

		namefile = file.split('.')[0] + '.txt'
		f = open(currdir+ datedir + '/' + namefile, 'w')
		f.write(ans)
		f.close()

# pathfile = testdir + 'main.html'

# data = open(pathfile, 'r')
# data = data.read()
# soup = BeautifulSoup(data, "lxml")

# soup = soup.find(id = 'item_pantip-trending')
# soup = soup.find_all('a')

# ans = []
# for i in soup:
# 	topic = i.get('href')
# 	if topic.startswith('/topic/'):
# 		ans.append(topic)

# print ans

# pathfile = testdir + 'food.html'

# data = open(pathfile, 'r')
# data = data.read()
# soup = BeautifulSoup(data, "lxml")

# soup = soup.find(id = 'item_pantip-trending_room')
# soup = soup.find_all('a')

# ans = []
# for i in soup:
# 	topic = i.get('href')
# 	if topic.startswith('/topic/'):
# 		ans.append(topic)

# print ans

# close()


# for i in soup:
	# print i.get('href')

# soup = soup.find_all('a')
# print soup

# for i in range(len(data)):
# 	if i == 0:
# 		continue;
# 	# break
# 	topic = data[i].split('topic/')[-1]
# 	topic = topic.split('"')[0]
# 	# print data[i]
# 	print ""
# 	print ""
# 	print ""
# 	print ""
# 	print topic