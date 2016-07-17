import csv
fileToProcess = "multi_readings.csv"
outputFile = "multi_readings.scl"
processedRows = -1
startProcessing = False
previousTime = -1
usedTime = 0
columns = [];

with open(outputFile,'w') as output:
    print("// Magic file created by Dude", file=output)
    print("configuration for \"pic16f18313\" is",file=output)
    print("end configuration;",file=output)
    print("",file=output)
    print("testbench for \"pic16f18313\" is",file=output)
    print("begin",file=output)
    print("\t//Pin/Register Actions",file=output)
    print("\tprocess is",file=output)
    print("\tbegin",file=output)
    with open(fileToProcess, 'r') as csvfile:
        reader = csv.reader(csvfile, dialect='excel')
        for row in reader:
            if (processedRows >= 0):
                if (previousTime == -1):
                    # First time getting the time
                    previousTime = int(row[0])
                    usedTime = int(row[0])
                else:
                    if (not row[0]):
                        break
                    usedTime = int(row[0]) - previousTime
                    previousTime = int(row[0])
                print("\t\t\twait for {} us;".format(usedTime),file=output)
                print("\t\t\treport \"Stimulus actions after " + row[0] + " us\";",file=output)
                for i in range(0,len(columns)):
                    # Grab the second column of the row to skip the time vector
                    column = row[i+1]
                    if column:
                        # If this isn't an empty string, print something
                        print("\t\t\t"+columns[i] +" <= '" + column + "';",file=output)                    
                #if (row[1] != ''):
                #    print("\t\t\tRA1 <= '" + row[1] + "';",file=output)
                #if (row[2] != ''):
                #    print("\t\t\tRA2 <= '" + row[2] + "';",file=output)

            if (startProcessing):
                if (processedRows == -1):
                    # Ready to get the names of the columns we have
                    for column in row:
                        columns.append(column)
                    # Pop off the first element (it's the time vector)
                    columns.pop(0)
                processedRows = processedRows + 1
                
                
            if (row[0]=="Begin Table"):
                startProcessing = True                
    print("\t\twait;",file=output)
    print("\tend process;",file=output)
    print("end testbench;",file=output)
        
