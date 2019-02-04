# Script that obtains various git metrics from a basic git log file
require 'set'
require 'date'

# Given an array of git log lines, count the number of commits in the log
def num_commits(lines)
  num = 0
  lines.each{ |line| num+=1 if line.start_with?("commit")}
  num 
end

# Given an array of git log lines, count the number of different authors
#   (Don't double-count!)
# You may assume that emails make a developer unique, that is, if a developer
# has two different emails they are counted as two different people.
def num_developers(lines)
  devs = Set.new
  lines.each do |line|
    if line.include?("Author")
	  x = line.split(" ").select{|x| x.include?("@")}
	  devs.add(x)
	end
  end
  devs.size  
end

# Given an array of Git log lines, compute the number of days this was in development
# Note: you cannot assume any order of commits (e.g. you cannot assume that the newest commit is first).
def days_of_development(lines)
  oldestDate = Date.new(2100)
  latestDate = Date.new(1900)
  noDates = true
  lines.each do |line|
    if line.start_with?("Date:")
      noDates = false
      data = line.split(" ")
      date = DateTime.parse(data[1..-1].join(" "))
      oldestDate = date if (date<=>oldestDate) == -1
      latestDate = date if (date<=>latestDate) == 1
    end  
  end
  return 0 if noDates
  (latestDate - oldestDate + 1).to_i
end

# This is a ruby idiom that allows us to use both unit testing and command line processing
# Does not get run when we use unit testing, e.g. ruby test_git_metrics.rb
# These commands will invoke this code with our test data: 
#    ruby git_metrics.rb < ruby-progressbar-short.txt
#    ruby git_metrics.rb < ruby-progressbar-full.txt
if __FILE__ == $PROGRAM_NAME
  lines = []
  $stdin.each { |line| lines << line }
  puts "Nunber of commits: #{num_commits lines}"
  puts "Number of developers: #{num_developers lines}"
  puts "Number of days in development: #{days_of_development lines}"
end

