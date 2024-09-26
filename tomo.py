import datetime

# Get the current date and time
now = datetime.datetime.now()

# Print the day and date
print("Today is", now.strftime("%A"), "and the date is", now.strftime("%B %d, %Y"))
