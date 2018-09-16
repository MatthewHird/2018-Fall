import re


class Assembler:
    opcodes = {'noop': '00000000', 'halt': '00000001', 'pushimm': '00000010',
               'pushext': '00000011', 'popinh': '00000100', 'popext': '00000101',
               'jnz': '00000110', 'jnn': '00000111', 'add': '00001000',
               'sub': '00001001', 'nor': '00001010'}

    def __init__(self):
        self.label_names = None
        self.mac_code = None
        self.label_list = None
        self.ass_instructions = None
        self.ass_operands = None
        self.ass_comments = None

    def run(self, input_string, comments=False):
        self.label_names = {'PSW': 'FFFB', 'A': 'FFFC', 'B': 'FFFD', 'C': 'FFFE', 'D': 'FFFF'}
        self.mac_code = []
        self.label_list = []
        self.ass_instructions = []
        self.ass_operands = []
        self.ass_comments = []
        self.__parse_assembly_string(input_string)
        mac_string = self.__build_mac_string(comments)

        return mac_string

    def __parse_assembly_string(self, assembly_string):
        self.assembly_inputs = []

        pc = 0
        for full_line in assembly_string.splitlines():
            line = full_line
            label = ''
            ass_instruct = None
            ass_oper = ''
            comment = ''
            arg_count = 0

            m1 = re.search('#', line)
            if m1:
                comment = line[m1.end():].strip()
                line = line[:m1.start()].strip()

            if re.fullmatch('\s*', line):
                ass_instruct = 'noop'
            else:
                m2 = re.match('[a-zA-Z]+:', line)
                if m2:
                    label = line[:m2.end() - 1]
                    self.label_names[label] = ('%X' % pc).zfill(4)

                    line = line[m2.end():].strip()

                m3 = re.search(' ', line)
                if m3:
                    ass_instruct = line[:m3.start()]
                    ass_oper = line[m3.start() + 1:]
                else:
                    ass_instruct = line

            if ass_instruct == 'pushimm':
                arg_count = 1
            elif ass_instruct == 'pushext':
                arg_count = 2
            elif ass_instruct == 'popext':
                arg_count = 2
            elif ass_instruct == 'jnz':
                arg_count = 2
            elif ass_instruct == 'jnn':
                arg_count = 2

            self.mac_code.append(self.opcodes.get(ass_instruct))
            self.label_list.append(label)
            self.ass_instructions.append(ass_instruct)
            self.ass_operands.append(ass_oper)
            self.ass_comments.append(comment)

            for i in range(arg_count):
                self.mac_code.append('')
                self.label_list.append('')
                self.ass_instructions.append('')
                self.ass_operands.append('')
                self.ass_comments.append('')
            pc += arg_count + 1

        line_count = pc
        pc = 0
        while pc < line_count:
            if self.ass_instructions[pc]:
                arg_count = 0
                if self.ass_instructions[pc] == 'pushimm':
                    arg_count = 1
                elif self.ass_instructions[pc] == 'pushext':
                    arg_count = 2
                elif self.ass_instructions[pc] == 'popext':
                    arg_count = 2
                elif self.ass_instructions[pc] == 'jnz':
                    arg_count = 2
                elif self.ass_instructions[pc] == 'jnn':
                    arg_count = 2

                if arg_count == 1:
                    operand = self.ass_operands[pc]
                    if re.fullmatch('[0-9A-Fa-f]{1,2}', operand):
                        self.mac_code[pc + 1] = bin(int(operand, 16)).replace('0b', '').zfill(8)
                    elif re.fullmatch('\+\d+', operand):
                        self.mac_code[pc + 1] = '0' + bin(int(operand[1:])).replace('0b', '').zfill(7)
                    elif re.fullmatch('-\d+', operand):
                        self.mac_code[pc + 1] = '1' + bin(int(operand[1:])).replace('0b', '').zfill(7)
                    elif re.fullmatch('[01]{8}', operand):
                        self.mac_code[pc + 1] = operand
                elif arg_count == 2:
                    operand = self.ass_operands[pc]
                    if self.label_names.get(operand):
                        operand = self.label_names.get(operand)
                    if re.fullmatch('[0-9A-Fa-f]{4}', operand):
                        self.mac_code[pc + 1] = bin(int(operand[:2], 16)).replace('0b', '').zfill(8)
                        self.mac_code[pc + 2] = bin(int(operand[2:], 16)).replace('0b', '').zfill(8)
                    elif re.fullmatch('[01]{16}', operand):
                        self.mac_code[pc + 1] = operand[:8]
                        self.mac_code[pc + 2] = operand[8:]
            pc += 1

    def __build_mac_string(self, comments):
        line_count = len(self.mac_code)
        mac_string = ''

        for pc in range(line_count):
            mac_string += self.mac_code[pc]
            if comments:
                if self.label_list[pc]:
                    mac_string += ' ' + self.label_list[pc] + ':'
                if self.ass_instructions[pc] and self.ass_instructions[pc] != 'noop':
                    mac_string += ' ' + self.ass_instructions[pc]
                if self.ass_operands[pc]:
                    mac_string += ' ' + self.ass_operands[pc]
                if self.ass_comments[pc]:
                    mac_string += '   # ' + self.ass_comments[pc]
            mac_string += '\n'
        mac_string = mac_string.strip()

        return mac_string


if __name__ == '__main__':
    pass
