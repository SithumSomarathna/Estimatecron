# Estimatecron

Analyses a fictional log of commands that have been executed during 2022 and their durations to provide statistics on 
  - which command was executed the most
  - the total number of commands executed
  - the maximum number of commands that ran concurrently at any particular time
during a particular month.

Input: 
Two .txt files: A crontab file and an estimates file. The crontab file has log information on what times during the year different commands were executed in the following form:
  - The crontab file can have 2 types of lines
      - Comment lines: lines whose first non-whitespace character is a '#'. Their contents are ignored
      - Command lines: consists of 6 words and/or numbers providing information about a command's execution
          - In the form: [minute] [hour] [date] [month] [day] [command_name]
          - The minute value must be between 0 and 59 or a '*' (representing an execution every minute)
          - The hour value must be between 0 and 23 or a '*' (representing an execution every hour)
          - The date value must be a valid date in the month of execution or a '*' (representing an execution on every day of the month)
          - The month can be written numerically (from 0 to 11) or by using 3-letter abbreviations ('jan' to 'dec') or a '*' (representing an execution every month)
          - The day can be written numerically (from 0 to 6, 0=sunday) or by using 3-letter abbreviations ('sun' to 'sat') or a '*' (representing an execution every day)
          - The command_name is simply a string that signifies the name of the command that was executed during the above timing parameters
          - Note that the command is only executed if both the date and day parameters are satisfied. It may be the case that both are given non '*' values and that there is no date in the given month that also has the given day. In this case, this command line is ignored
          - E.g. "30 * * jun sun backup" means that the command 'backup' was executed on the 30th minute of every hour on any date of June that was a Sunday
          - E.g. "15 23 * * * record" means that the command 'record' was executed at 11:15pm of every day of every month
          - E.g. "* 10 1 * 0 new" means that the command 'new' was executed every minute between 10am and 11am (the 10th hour) on any day of any month where the 1st date was a Sunday
          - E.g. "* * 3 jul sat imp" this command will be ignored as in 2022, the 3rd of July is not a Saturday
  - The estimates file can have 2 types of lines
      - Comment lines: lines whose first non-whitespace character is a '#'. Their contents are ignored
      - Estimate lines: consists of 1 word and 1 number providing information about how long a command takes to be executed
          - In the form [command_name] [run_time]
          - The command_name is simply a string that signifies the name of the command that this line has run-time information about
          - The run_time is the number of minutes it takes for this specific command to execute
A pair of example inputs for a crontab file - crontab-file1.txt and a estimates file - estimates-file1.txt are provided.

Usage: 
Firstly ensure that the program is compiled - a Makefile has been provided. 
In the command line, enter: ./estimatecron [month] [crontab file] [estimates file]
Month is the month that we want the statistics for, represented either as a numerical value from 0 to 11 or as a 3-letter abbreviation of the month ('jan' to 'dec').
Crontab file is the name of the crontab file
Estimates file is the name of the estimates file

Output: 
The name of the command that was executed the most during the given month
The total number of commands that were executed during the given month
The maximum number of commands that were running concurrently during the given month

Specifications:
- Both the crontab and estimates file have a maximum of 20 command lines each
- Each command line is at most 100 characters long and each command name is at most 40 character long
- If a command ends in the same minute as another command starting, it is assumed that the finishing command will terminate before the starting command begins execution
- Each command will terminate before a new month starts (no commands carry over onto successive months)

          
      
