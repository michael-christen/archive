# -*- coding: utf-8 -*-
#define list of urls, how to follow links, and parse contents of page
#to extract items
import scrapy
import urllib
import re
import target
import urlparse

from pdf_downloader.items import PdfDownloaderItem



parsed_url = urlparse.urlparse(target.TARGET_URL)
class FirstSpiderSpider(scrapy.Spider):
	name = "first_spider"
	allowed_domains = [parsed_url.netloc]
	start_urls = (
			target.TARGET_URL,
	)

	def parse(self, response):
		#response is pdf document
		m = re.search('([^\/]+\.pdf)$',response.url)
		if m:
			item = PdfDownloaderItem()
			item['link'] = response.url
			item['name'] = m.group(1)
			item['local_location'] = target.TARGET_DEST+'/'+ item['name']
			#save actual file
			with open(item['local_location'], 'w') as f:
				f.write(response.body)
			yield item
		#have pdf links, so crawl again to save
		else:
			for url in response.xpath('//a/@href').re('(.+\.pdf)'):
				new_url = urlparse.urljoin(response.url,url)
				yield scrapy.Request(new_url, callback=self.parse)
		pass

