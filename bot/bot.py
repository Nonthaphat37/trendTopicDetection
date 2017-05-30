from selenium import webdriver
from selenium.webdriver.support.ui import WebDriverWait
from selenium.common.exceptions import WebDriverException
 
rooms = ['food', 'greenzone', 'camera', 'cartoon', 'gallery', 'klaibann', 'jatujak', 'chalermkrung', 'chalermthai', 'family', 'home', 'siliconvalley', 'beauty', 'writer', 'blueplanet', 'tvshow', 'bangrak', 'horoscope', 'pantip', 'region', 'mbk', 'ratchada', 'isolate', 'social', 'supachalasai', 'siam', 'sinthorn', 'silom', 'wahkor', 'library', 'art']

date = '30-5-2017-0000'

# wait for ajax to loads
def wait_ajax(driver):
	try:
		return 0 == driver.execute_script("return jQuery.active")
	except WebDriverException:
		pass
 
def get_webpage():
	file = open('pantip/' + date + '/' + 'main' + '.html', 'w')
	ff_driver = webdriver.Chrome('/Users/nonthaphat/Research/SeniorProject/bot/chromedriver')
	ff_driver.get('https://pantip.com/#trend')
	WebDriverWait(ff_driver, 10).until(wait_ajax,  "Timeout waiting for page to load")
	file.write(ff_driver.page_source.encode('utf-8'))
	ff_driver.close()
	file.close()

	for i in rooms:
		print i
		file = open('pantip/'  + date + '/' + i + '.html', 'w')
		ff_driver = webdriver.Chrome('/Users/nonthaphat/Research/SeniorProject/bot/chromedriver')
		ff_driver.get("https://pantip.com/forum/" + i)
		ff_driver.find_element_by_id('room_trend').click()
		WebDriverWait(ff_driver, 10).until(wait_ajax,  "Timeout waiting for page to load")
		file.write(ff_driver.page_source.encode('utf-8'))
		ff_driver.close()
		file.close()

get_webpage()