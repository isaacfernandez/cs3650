#Isaac Fernandez
#hw07

#List 1, sum3
def sum3(nums):
  return sum(nums)

def rotate_left3(nums):
  return nums[1:] + nums[:1]

#list 1, max_end3
def max_end3(nums):
  return [max([nums[0], nums[2]]) for n in nums];

#Python > List-1 > make_ends
def make_ends(nums):
  return [nums[0], nums[len(nums)-1]]

#Python > List-1 > has23
def has23(nums):
  return 2 in nums or 3 in nums

#Python > List-2 > count_events
def count_evens(nums):
  return len( [n for n in nums if n%2 == 0] )

#Python > List-2 > sum13

def sum13(nums):
  return sum([nums[i] for i in range(len(nums)) if nums[i] != 13 and (i == 0 or nums[i-1] != 13)])

#Python > List-2 > big_diff
def big_diff(nums):
  return max(nums) - min(nums)

#Python > List-2 > sum67
def sum67(nums):
  while 6 in nums:
    rest = nums[nums.index(6):]
    nums = nums[:nums.index(6)] + rest[rest.index(7)+1:]
  return sum(nums)

#Python > List-2 > centered_average
def centered_average(nums):
  return (sum(nums) - (min(nums) + max(nums))) / (len(nums) - 2)

#Python > List-2 > has22
def has22(nums):
  for i in range(len(nums) - 1):
    if nums[i] == nums[i+1] == 2:
      return True
  return False

#Python > String-1 > extra_end 
def extra_end(str):
  return 3*str[-2:]

#Python > String-1 > without_end 
def without_end(str):
  return str[1:-1]

#Python > String-2 > double_char
def double_char(str):
  return ''.join([c + c for c in str])

#Python > String-2 > count_code
def double_char(str):
  return ''.join([c + c for c in str])

#Python > String-2 > count_hi
def count_hi(str):
  return str.count('hi')

#Python > String-2 > end_other
def count_code(str):
  sum = 0
  for i in range(len(str)-3):
        if (str[i:i+2] == 'co') and (str[i+3] == 'e'):
          sum += 1
  return sum

#Python > String-2 > cat_dog
def cat_dog(str):
  return str.count('dog') == str.count('cat')

#Python > String-2 > xyz_there
def xyz_there(str):
  return str.count('xyz') > str.count('.xyz')

#I'm aware this could be done in one line
#I named variables simply for horizontal brevity
def wc(str):
	newlines = str.count('\n')
	words = len(str.split(' '))
	chars = len(str) - newlines
	return [newlines, words, chars]

def mycount(str):
	mycount = [ str.count(c) for c in "0123456789 \t\n" ]
	return [m for m in mycount]