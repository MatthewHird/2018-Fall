class Error(Exception):
    def __init__(self, message):
        self.message = message


class InvalidLabelError(Error):
    def __init__(self, label_name, ass_line_count):
        self.label_name = label_name
        self.message = 'InvalidLabelError: "' + label_name + '" label on assembly line ' + str(ass_line_count) + \
                       ' is not a valid label name. '


class DuplicateLabelError(Error):
    def __init__(self, label_name, ass_line_count):
        self.label_name = label_name
        self.message = 'DuplicateLabelError: "' + label_name + '" label on assembly line ' + str(ass_line_count) + \
                       ' already exists.'


class LabelShadowMemoryLocationError(Error):
    def __init__(self, label_name, ass_line_count):
        self.label_name = label_name
        self.message = 'LabelShadowMemoryLocationError: "' + label_name + '" label on assembly line ' + str(ass_line_count) \
                       + ' is an uppercase four digit hexadecimal value, which shadows a memory location.'


class AssemblyOpcodeError(Error):
    def __init__(self, input_opcode, ass_line_count):
        self.input_opcode = input_opcode
        self.message = 'AssemblyOpcodeError: "' + input_opcode + '" on assembly line ' + str(ass_line_count) \
                       + ' is not a valid opcode.'


class InvalidOperandError(Error):
    def __init__(self, input_operand, mac_line_count):
        self.input_operand = input_operand
        self.message = 'AssemblyOperandError: "' + input_operand + '" on mac line ' + str(mac_line_count) \
                       + ' is not a valid operand.'
