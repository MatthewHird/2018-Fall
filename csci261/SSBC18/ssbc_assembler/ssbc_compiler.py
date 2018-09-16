from assembler import Assembler


class SsbcCompiler:
    @classmethod
    def build_file(cls, in_file_path="test.ass", out_file_path="test.mac", comments=False, display=False):
        assembler = Assembler()
        ass_file_string = cls.__load_file(in_file_path)
        mac_file_string = assembler.run(ass_file_string, comments)
        if out_file_path:
            cls.__write_file(out_file_path, mac_file_string)
        if display:
            print(mac_file_string)

    @staticmethod
    def __load_file(file_path):
        file = open(file_path, 'r')
        file_string = file.read()
        file.close()

        return file_string

    @staticmethod
    def __write_file(file_path, contents):
        file = open(file_path, 'w')
        file.write(contents)
        file.close()


if __name__ == '__main__':
    SsbcCompiler.build_file(comments=True, display=True)
