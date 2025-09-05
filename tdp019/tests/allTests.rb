require_relative '../parser.rb'

base_path = File.dirname(__FILE__)

files = ["assignTests.rb", "boolTests.rb", "exprTests.rb", "funcTests.rb", "ifTests.rb", "printTests.rb", "recursiveTests.rb", "whileTests.rb", "llistTests.rb", "classTests.rb", "overrideTests.rb", "overrideTests2.rb"]

files.each do |file|
  file_path = File.join(base_path, file)
  success = system("ruby #{file_path}")
  unless success
    raise "Testfilen #{file} misslyckades."
  end
end

puts "Alla tester passerade."