import argparse
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
    parser = argparse.ArgumentParser(description='Compile SSBC18 assembly code to SSBC18 machine code.')
    parser.add_argument('infile', help='path of assembly code file to process')
    parser.add_argument('outfile', default='mac', nargs='?',
                        help='path of machine code file create (default: \'./mac\')')
    parser.add_argument('-c', '--comments', action='store_true',
                        help='flag to add assembly comments to machine code file')
    parser.add_argument('-d', '--display', action='store_true',
                        help='flag to display created machine code in terminal')

    args = parser.parse_args()
    SsbcCompiler.build_file(in_file_path=args.infile, out_file_path=args.outfile,
                            comments=args.comments, display=args.display)
