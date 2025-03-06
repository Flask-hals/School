require 'rexml/document'

src = File.read("events.html")
doc = REXML::Document.new(src)
root = doc.root

arr = Array.new

def get_summary(e)
  e.each_element(".//span[@class = 'summary']") {|e| return e.text}
end

def get_dstart(e)
  e.each_element(".//span[@class = 'dtstart']") {|e| return e.text}
end

def get_userlink(e)
  e.each_element(".//a[@class = 'userLink ']") {|e| return e.text}
end

def get_locality(e)
  e.each_element(".//span[@class = 'locality']") {|e| return e.text}
end

def get_region(e)
  e.each_element(".//span[@class = 'region']") {|e| return e.text}
end

def get_street(e)
  e.each_element(".//span[@class = 'street-address']") {|e| return e.text}
end

def get_description(e)
  e.each_element(".//td[@class = 'description']") {|e|
    e.each_element(".//p") {|e| return e.text}}
end

def build_hash(e)
  hash =  {}
  hash[:summary] = get_summary(e)
  hash[:dstart] = get_dstart(e)
  hash[:userlink] = get_userlink(e)
  hash[:locality] = get_locality(e)
  hash[:region] = get_region(e)
  hash[:street] = get_street(e)
  hash[:description] = get_description(e)
  return hash
end

root.each_element("//div[@class = 'vevent']") {|e| arr.insert(-1, build_hash(e))}

def print_arr(arr)
  for elem in arr
    puts elem
    puts " "
  end
end

print_arr(arr)