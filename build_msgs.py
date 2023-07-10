import os

print("Beginning message build script...")

target = "include/mercury/msgs/"
specs = target + "specs/"
dir = os.fsencode(specs)

msg_names = []
# For each file in mercury/msgs/specs
for file in os.listdir(dir):
    # Open file
    filename = os.fsdecode(file)

    if filename.endswith(".msg"):
        msg_name = filename[0:-4]
        # Save header name in list
        msg_names.append(msg_name)

        content = open(specs + filename)
        
        # Read contents and decide structure of message
        struct_fields = {}
        for line in content:
            type_and_name = line.split()
            struct_fields[type_and_name[1]] = type_and_name[0]
        
        content.close()
        
        # Create and write to <message_name>.h (use mercury::msgs namespace)
        new_header = open(target + msg_name + ".h", "w")
        new_header.write("#pragma once\n\n")
        new_header.write("#include <string>\n")
        new_header.write("#include <vector>\n\n")
        new_header.write("namespace mercury {\n\n")
        new_header.write("using std::string;\n")
        new_header.write("using std::vector;\n\n")

        new_header.write("struct " + msg_name + " {\n")
        for name in struct_fields:
            new_header.write("\t" + struct_fields[name] + " " + name + ";\n")
        new_header.write("};\n\n")

        new_header.write("}\n")

# Write all header names to message.h
msg_header = open(target + "message.h", "w")
msg_header.write("#pragma once\n\n")
msg_header.write("#include <variant>\n\n")

for name in msg_names:
    msg_header.write("#include \"" + target[8:] + name + ".h\"\n")

msg_header.write("\nnamespace mercury {\n\n")

# Create variant with all messages
all_names = ""
for name in msg_names:
    all_names += name + ", "
all_names = all_names[:-2]

msg_header.write("using Message = std::variant<" + all_names + ">;\n\n")

# Create visitor struct
msg_header.write("struct visitor {\n")
for name in msg_names:
    msg_header.write("\tvoid operator()(" + name + "&) {}\n")
msg_header.write("};\n\n")

# Close namespace
msg_header.write("}\n")

print("Message code generated!")
