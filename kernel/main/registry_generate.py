import sys

with open(sys.argv[1], 'r') as f:
    pairs = [line.strip().split() for line in f if line.strip()]

print("// Auto-generated registry")
print("")
print("FuncEntry command_registry[] = {")
for cmd, func in pairs:
    print(f'    {{ "{cmd}", {func} }},')
print("    { NULL, NULL }")
print("};")
