/*
* SOL1 Lab6 20210203
* WS2020
* Prof. Schoenen
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h> /* for tolower() */
#define _USE_MATH_DEFINES /* for M_PI */
#include <math.h>
#include <stdlib.h> /* for rand() */
#include <time.h> /* for time() in srand() */
#include <stdint.h> /* for int16_t */
#include <limits.h> /* for SHRT_MAX etc */

// global:
//#define DEBUG 1 /* 1==true to give a lot of output */
int DEBUG = 0;
int arg_list_start_index = 1; // where do the arguments start?
							  // global variables: (!!!)
const char FILLER = '.'; // what to print instead of unprintable chars
int flag_hexdump_real_address_print = 1; // 1=on, 0=off
typedef unsigned char byte; // BYTE :-)

void hexdump(void *address, int size) {
	if (DEBUG) printf("hexdump(%p)\n", address);
	int remaining = 16;;
	int remaining_last_line = size % 16; if (remaining_last_line == 0) remaining_last_line += 16;
	int size_rounded_up = size + (16 - remaining_last_line);
	for (int i = 0; i < size_rounded_up; i++) {
		if (i % 16 == 0) /* print address every 16 bytes */
			if (flag_hexdump_real_address_print)
				printf("%08X ", (unsigned int)((byte *)address + i));
			else
				printf("%08X ", i); // just offset
		if (i < size) {
			printf(" %02X", *((byte *)address + i));
		} else {
			printf("   "); // empty, i.e. we are in the last line
			remaining = remaining_last_line;
		}
		if (i % 16 == 15) {
			printf("  ");
			for (int j = 0; j < remaining; j++) {
				char c = *((byte *)address + (i - 15) + j);
				if (c<32) { c = FILLER; } // non-printable
				printf("%c", c);
			}
			printf("\n");
		}
	}
	printf("\n");
} // hexdump

char* sprintbin(char* buffer, byte digits, unsigned long long number) {
	int bits = sizeof(number) * 8; // 8*8=64
	if (digits < bits) bits = digits; // minimum
	int index = 0;
	for (int bitpos = bits - 1; bitpos >= 0; bitpos--) {
		char c = '0';
		unsigned long long maske = 1LL << bitpos;
		if (number & maske) c = '1';
		buffer[index++] = c;
	}
	buffer[index] = '\0'; // Stringende !
	return buffer;
} // sprintbin

/**********************************************************
* WAV specific structures
**********************************************************/

// WAV header spec information:
// https://en.wikipedia.org/wiki/WAV
// https://de.wikipedia.org/wiki/RIFF_WAVE
// https://web.archive.org/web/20140327141505/https://ccrma.stanford.edu/courses/422/projects/WaveFormat/
// http://www.topherlee.com/software/pcm-tut-wavformat.html
// https://gist.github.com/Jon-Schneider/8b7c53d27a7a13346a643dac9c19d34f

typedef enum { PCM_FORMAT = 1, PCM_CHUNK = 16 } wav_format_constants;

typedef struct wav_header_type {
	// RIFF Header
	char riff_header[4]; // Contains "RIFF"
	int wav_size; // Size of the wav portion of the file, which follows the first 8 bytes. File size - 8
	// the wav_size starts counting here.
	char wave_header[4]; // Contains "WAVE"
	// Format Header
	char fmt_header[4]; // Contains "fmt " (includes trailing space)
	// offset 16
	int fmt_chunk_size; // Should be 16 for PCM
	short audio_format; // Should be 1 for PCM. 3 for IEEE Float
	short num_channels; // 1 = mono, 2 = stereo
	int sample_rate; // usually 44100 Sa/s
	int byte_rate; // Number of bytes per second. sample_rate * num_channels * Bytes Per Sample
	short sample_alignment; // num_channels * Bytes Per Sample
	short bit_depth; // Number of bits per sample; usually 16 Bits for PCM, i.e. 2 BytesPerSample
	// Data
	char data_header[4]; // Contains "data"
	int data_bytes; // Number of bytes in data. Number of samples * num_channels * sample byte size
	// uint8_t bytes[]; // Remainder of wave file is bytes
} wav_header_type;

wav_header_type wav_header_template =
{ "RIFF", 0, "WAVE", "fmt ", PCM_CHUNK, PCM_FORMAT, 0, 0, 0, 0, 0, "data", 0 };

typedef struct wav_trailer_begin_type {
	char keyword_list[4]; // Contains "LIST"
	int trailer_size_bytes;
	char keyword_info[4]; // Contains "INFO"
} wav_trailer_begin_type;

typedef struct wav_trailer_chunk_type {
	char keyword[4]; // Contains "LIST" or "INAM" or "IPRD" ...
	int following_string_size;
	//char following_string[0]; // zero-length array https://gcc.gnu.org/onlinedocs/gcc/Zero-Length.html
	char following_string[]; // flexible-length array https://gcc.gnu.org/onlinedocs/gcc/Zero-Length.html
} wav_trailer_chunk_type;

// this functions fills the WAV structure with default data
void create_wav_header(wav_header_type *wav_header, long num_samples) {
	if (DEBUG) printf("create_wav_header(%p,%ld)\n", wav_header, num_samples);
	// here you need to fill the structure fields. Use values like in other wav files.
	*wav_header = wav_header_template; // copy over complete template
	/* strcpy(wav_header->riff_header, "RIFF");	strcpy(wav_header->wave_header, "WAVE"); strcpy(wav_header->fmt_header, "fmt "); strcpy(wav_header->data_header, "data"); */
	wav_header->wav_size = sizeof(wav_header_type)-8+num_samples*2;
	wav_header->fmt_chunk_size = 16;
	wav_header->audio_format = 1;
	wav_header->num_channels = 1;
	wav_header->sample_rate  = 44100;
	wav_header->byte_rate    = 88200;
	wav_header->sample_alignment = 2;
	wav_header->bit_depth  = 16;
	wav_header->data_bytes = num_samples * 2;
	wav_header->bit_depth  = 16;
	if (DEBUG) hexdump(wav_header, sizeof(wav_header_type));
}

/**********************************************************
****************   BEGIN of student code   ****************
**********************************************************/

// indicator for student progress. Set contents in main(). Default OFF.
struct student_progress {
	int task4;
	int task5;
	int task6;
	int task7;
	int task8;
	int task9;
	int task10;
} student_has_implemented = { 0 };

// Student code Task 3:
void clean_string(char *emmanuel_duru, char *better_ascii_student_name) {
	if (DEBUG) printf("clean_string(%p,%p)\n", emmanuel_duru, better_ascii_student_name);
	//strcpy(better_ascii_student_name, student_name); // copy over without modification
	// your code here
	char character_number; // c to get ASCII character number
	//printf("strlen(student_name) = %d\n", strlen(student_name));
	for (int i = 0; i < strlen(emmanuel_duru); i++) {
		//printf("%c\n", student_name[i]);
		character_number = emmanuel_duru[i];
		if (character_number == ' ') { // if c = [space], change to '_'
			better_ascii_student_name[i] = '_';
		}
		else if (character_number > 64 && character_number < 97) { // if c is capital, add 32 to make it small
			better_ascii_student_name[i] = character_number + 32;
		}
	}


	if (DEBUG) printf("clean_string(%p,%p) = \"%s\"\n",
		emmanuel_duru, better_ascii_student_name, better_ascii_student_name);
} // clean_string

// Student code Task 4:
void plot_samples(char *filename, int16_t *memoryblock, long num_samples, int16_t min, int16_t max) {
	if (DEBUG) printf("plot_samples(\"%s\",%p,%ld,%hd,%hd)\n",
		filename, memoryblock, num_samples, min, max);
	// your code here
	// declare an array and fill with values from the file
	if (DEBUG) printf("memoryblock starts from %p\n", memoryblock);
	int16_t array_plot[100]; // array declaration

	for (int i = 0; i < num_samples; i++) {
		array_plot[i] = *(memoryblock + i);
		if (DEBUG) printf("plot_array[%d] = %d\n", i, array_plot[i]);
	}

	// setting some parameters needed for plot to function
	double region = max - min; // defining range of values
	int column, COL = 80; // definition of the width and column
	if (DEBUG) printf("\nmin is %hd, max is %hd, range is %lf\n\n", min, max, region);

	// plotting array to the screen
	for (int i = 0; i < num_samples; i++) {
		column = ((array_plot[i] - (int)min) / region) * COL; // calling the column value
		printf("%d ", column); // printing the column value

		for (int i = 0; i < COL; i++) {
			if (i == column) printf("*"); // printing "*" on the screen when we attain the max column
			else printf(" ");
		}
		printf("\n");
	}
} // plot_samples


// Student code Task 5:
int plot_samples_into_file(char *filename, int16_t *memoryblock, long num_samples, int16_t min, int16_t max) {
	if (DEBUG) printf("plot_samples_into_file(\"%s\",%p,%ld,%hd,%hd)\n",
		filename, memoryblock, num_samples, min, max);
	// your code here
	char fname[64]; // create a string array to store new file name
	strcpy(fname, filename); // copy current filename to new array
	strcat(fname, ".txt"); // add .txt to new file name
	if (DEBUG) printf("The new filename is %s\n", fname); // print out the new file name
	printf("num_samples is %d\n", num_samples); // print out the number of samples

	// declare an array and fill with values from the file
	if (DEBUG) printf("memoryblock starts from %p\n", memoryblock);
	int16_t plot_array[10000]; // declaring an array
	for (int i = 0; i < num_samples; i++) {
		plot_array[i] = *(memoryblock + i);
		//if (DEBUG) printf("plot_array[%d] = %d\n", i, plot_array[i]);
	}

	// setting some parameters needed for plot to function
	double range = max - min; // defining range of values
	int column, COL = 80; // defining column value and column width
	if (DEBUG) printf("\nmin is %hd, max is %hd, range is %lf\n\n", min, max, range);

	// declare a FILE pointer
	FILE* fp;
	printf("\nfname is %s\n", fname);
	fp = fopen(fname, "w");

	if (fp) { // if fopen() works
		// plotting array to file
		for (int i = 0; i < num_samples; i++) {
			column = ((plot_array[i] - (int)min) / range) * COL; // getting a column value
			//fprintf(fp, "%d ", column); // printing the column value

			for (int i = 0; i < COL; i++) {
				if (i == column) fprintf(fp, "*"); // printing "*" to the screen when column value reached
				else fprintf(fp, " ");
				//if (i == column) printf("*"); // printing "*" to the screen when column value reached
				//else printf(" ");
			}
			fprintf(fp, "\n");
			//printf("\n");
		}
		fclose(fp);
		printf("Plot written to %s successfully.\n\n", fname);
		return EXIT_SUCCESS;
	}
	else { // if fopen() fails
		fprintf(stderr, "Error: Cannot open file...\n");
		perror("Reason");
		return EXIT_FAILURE;
	}


} // plot_samples_into_file

// Student code Task 6:
// this function writes a block of memory into a binary file
int write_binary_file_generic(char *filename, void *buffer, long filesize) {
	if (DEBUG) printf("write_binary_file_generic(\"%s\",%p,%ld)\n", filename, buffer, filesize);
	// your code here



} // write_binary_file_generic

// Student code Task 7 (code fully provided):
// write_wav_file_empty(better_ascii_student_name);
int write_wav_file_empty(char *filename) {
	if (DEBUG) printf("write_wav_file_empty(\"%s\")\n",filename);
	long num_samples = 0;
	int filesize = sizeof(wav_header_type);
	// first get some memory for the header
	// malloc is the best solution, but a fixed array would work here, too.
	wav_header_type *buffer =
		(wav_header_type *)malloc(filesize);
	if (DEBUG) printf("malloc(%d)=%p\n", filesize, buffer);
	create_wav_header(buffer, num_samples);
	int rv = write_binary_file_generic(filename, buffer, filesize);
	free(buffer);
	return rv;
} // write_wav_file_empty

// Student code Task 8 (code fully provided):
// write_wav_file_sinewave(better_ascii_student_name, frequency, duration);
int write_wav_file_sinewave(char *filename, double frequency, double duration) {
	if (DEBUG) printf("write_wav_file_sinewave(\"%s\",t=%.1lf)\n", filename, duration);
	long samplerate = 44100;
	double scaling_factor = 0.5*INT16_MAX;
	if (DEBUG) printf(" - scaling_factor = %.1lf\n", scaling_factor);
	long num_samples = (long)(duration*samplerate);
	if (DEBUG) printf(" - num_samples = %ld\n", num_samples);
	int filesize = sizeof(wav_header_type) + 2*num_samples;
	// first get some memory for the header
	// malloc is the best solution, but a fixed array would work here, too.
	byte *buffer = malloc(filesize);
	if (DEBUG) printf("malloc(%d)=%p\n", filesize, buffer);
	create_wav_header((wav_header_type *)buffer, num_samples);
	int16_t *samples = (int16_t *)(buffer + sizeof(wav_header_type)); // address for samples
	for (long sample_index = 0; sample_index < num_samples; sample_index++) {
		double time = (double)sample_index / (double)samplerate;
		samples[sample_index] = (int16_t)(scaling_factor * sin(2.0*M_PI*frequency*time));
	}
	int rv = write_binary_file_generic(filename, buffer, filesize);
	free(buffer);
	return rv;
} // write_wav_file_sinewave

// Student code Task 9 (code fully provided):
// write_wav_file_octave(better_ascii_student_name, frequency, duration);
int write_wav_file_octave(char *filename, double frequency, double duration) {
	if (DEBUG) printf("write_wav_file_octave(\"%s\",%.1lf)\n", filename, duration);
	long samplerate = 44100;
	double scaling_factor = 0.5*INT16_MAX;
	if (DEBUG) printf(" - scaling_factor = %.1lf\n", scaling_factor);
	long num_samples_per_note = (long)(duration*samplerate);
	long num_samples = 13*num_samples_per_note; // 12 per octave plus C again.
	long next_note_sample_index = num_samples_per_note;
	if (DEBUG) printf(" - num_samples = %ld\n", num_samples);
	int filesize = sizeof(wav_header_type) + 2*num_samples;
	// first get some memory for the header
	// malloc is the best solution, but a fixed array would work here, too.
	byte *buffer = malloc(filesize);
	if (DEBUG) printf("malloc(%d)=%p\n", filesize, buffer);
	create_wav_header((wav_header_type *)buffer, num_samples);
	int16_t *samples = (int16_t *)(buffer + sizeof(wav_header_type)); // address for samples
	for (long sample_index = 0; sample_index < num_samples; sample_index++) {
		double time = (double)sample_index / (double)samplerate;
		if (sample_index>=next_note_sample_index) { // change note here
			next_note_sample_index += num_samples_per_note;
			frequency *= pow(2.0,1.0/12.0); // 12 notes per octave
			if (DEBUG) printf(" - frequency = %.3lf\n", frequency);
		}
		samples[sample_index] = (int16_t)(scaling_factor * sin(2.0*M_PI*frequency*time));
	}
	int rv = write_binary_file_generic(filename, buffer, filesize);
	free(buffer);
	return rv;
} // write_wav_file_octave

typedef struct musical_note {
	double frequency;
	double duration;
} tMusicalNote;

#define MAX_NOTES 20
typedef struct melody {
	unsigned int number_of_notes;
	tMusicalNote note[MAX_NOTES];
} tMelody;


// Student code Task 10:
// write_wav_file_melody(better_ascii_student_name, melody);
int write_wav_file_melody(char *filename, tMelody melody) {
	if (DEBUG) printf("write_wav_file_melody(\"%s\")\n", filename);
	long samplerate = 44100;
	double scaling_factor = 0.5*INT16_MAX;
	if (DEBUG) printf(" - scaling_factor = %.1lf\n", scaling_factor);
	double melody_duration = 0.0;
	for (int note_index = 0; note_index < melody.number_of_notes; note_index++) {
		melody_duration += melody.note[note_index].duration;
	}
	if (DEBUG) printf(" - melody_duration = %.1lf\n", melody_duration);
	long num_samples = (long)(melody_duration*samplerate);
	if (DEBUG) printf(" - num_samples = %ld\n", num_samples);
	int filesize = sizeof(wav_header_type) + 2 * num_samples;
	byte *buffer = malloc(filesize);
	if (DEBUG) printf("malloc(%d)=%p\n", filesize, buffer);
	create_wav_header((wav_header_type *)buffer, num_samples);
	int16_t *samples = (int16_t *)(buffer + sizeof(wav_header_type)); // address for samples
	long sample_index = 0;
	// iterate over all the notes of the melody:
	for (int note_index = 0; note_index < melody.number_of_notes; note_index++) {
		double f = melody.note[note_index].frequency;
		double d = melody.note[note_index].duration;
		if (DEBUG) printf(" #%d (f,d) = (%.3lf,%.1lf)\n", note_index, f,d);
		long note_samples = (long)(d*samplerate);
		// produce enough samples for one note:
		for (long index = 0; index < note_samples; index++) {
			double time = (double)index / (double)samplerate;
			int16_t value = (int16_t)(scaling_factor * sin(2.0*M_PI*f*time));
			if (note_samples - index < 1000) value = 0;
			samples[sample_index] = value;
			sample_index++;
		}
	}
	if (DEBUG) printf(" - last sample_index = %ld\n", sample_index);
	int rv = write_binary_file_generic(filename, buffer, filesize);
	free(buffer);
	return rv;
}

/**********************************************************
****************    END of student code    ****************
**********************************************************/

long get_filesize(FILE *fp) {
	// https://man7.org/linux/man-pages/man3/fseek.3.html
	fseek(fp, 0, SEEK_END); // position read pointer to the very end
	long end = ftell(fp); // at which position are we now?
	rewind(fp); // read pointer back to origin
	return end; // this is the filesize
} // get_filesize


//check_wav_trailer(address_after_samples, trailer_size);
void check_wav_trailer(byte *memoryblock, int trailer_size) {
	if (DEBUG) printf("check_wav_trailer(%p,%ld)\n", memoryblock, trailer_size);
	// first block is 12 Bytes of structure, so type-cast it:
	wav_trailer_begin_type *wav_trailer_begin = (wav_trailer_begin_type *)memoryblock;
	printf("keyword_list = \"%4.4s\"\n", wav_trailer_begin->keyword_list);
	int trailer_size_bytes = wav_trailer_begin->trailer_size_bytes;
	printf("trailer_size_bytes = %d = 0x%08X\n", trailer_size_bytes, trailer_size_bytes);
	printf("keyword_info = \"%4.4s\"\n", wav_trailer_begin->keyword_info);
	byte *chunk_pointer = memoryblock + sizeof(wav_trailer_begin_type);
	// iterate through all following chunks of information:
	while (chunk_pointer < memoryblock + trailer_size) {
		if (DEBUG) printf("chunk_pointer=%p\n", chunk_pointer);
		wav_trailer_chunk_type *wav_trailer_chunk = (wav_trailer_chunk_type *)chunk_pointer;
		printf("chunk_keyword = \"%4.4s\"\n", wav_trailer_chunk->keyword);
		int string_size = wav_trailer_chunk->following_string_size;
		printf("string_size = %d\n", string_size);
		// luckily the strings are 0-terminated :-)
		printf("string[%02d] = \"%s\"\n",
			string_size, &(wav_trailer_chunk->following_string));
		if (strncmp("id3", wav_trailer_chunk->following_string, 3)==0)
			break; // ignore ID3 info for now. ToDo later.
		int offset = sizeof(wav_trailer_chunk_type)+string_size;
		printf("offset = %d\n", offset); // must be 8+string_size
		chunk_pointer += offset;
	}
} // check_wav_trailer

// analyse WAV contents
void use_pcm_16bit(char *filename, int16_t *memoryblock, long num_samples) {
	// must be signed 16-bit data
	if (DEBUG) printf("use_pcm_16bit(\"%s\",%p,%ld)\n", filename, memoryblock, num_samples);
	int16_t amplitude_max = SHRT_MIN; // -32767
	int16_t amplitude_min = SHRT_MAX; // +32768
	//if (DEBUG) printf("amplitude min ... max = %hd .. %hd\n", amplitude_min, amplitude_max);
	for (long sample_index = 0; sample_index < num_samples; sample_index++) {
		int sample = memoryblock[sample_index]; // in multiples of 2 Bytes
		//if (sample_index<100) printf("sample[%06ld] = %6d\n", sample_index, sample);
		// ToDo: calculate statistics of all samples ...
		if (sample > amplitude_max) amplitude_max = sample;
		if (sample < amplitude_min) amplitude_min = sample;
	}
	int range = amplitude_max - amplitude_min;
	printf("amplitude min ... max = %hd .. %hd (%d)\n", amplitude_min, amplitude_max, range);
	float range_dynamics = (float)range / (float)USHRT_MAX; // /65636
	printf("amplitude dynamics = %.6f (%.3f%%)\n", range_dynamics, range_dynamics*100.0);
	if (student_has_implemented.task4) {
		long limit = (num_samples>100) ? 100 : num_samples; // smaller of the two
		plot_samples(filename, memoryblock, limit, amplitude_min, amplitude_max);
	}
	if (student_has_implemented.task5) {
		long limit = (num_samples>10000) ? 10000 : num_samples; // smaller of the two
		int rv = plot_samples_into_file(filename, memoryblock, limit, amplitude_min, amplitude_max);
		if (rv) exit(rv); // Error -> exit
	}
} // use_pcm_16bit

// see lecture 20210128
//check_wav_structure(filename,memoryblock, filesize);
void check_wav_structure(char *filename, byte *memoryblock, long filesize) {
	if (DEBUG) printf("check_wav_structure(\"%s\",%p,%ld)\n", filename, memoryblock, filesize);
	wav_header_type *wav_header = (wav_header_type*)memoryblock;
	printf("wav_size = %d\n", wav_header->wav_size);
	printf("- wav_size+8 = %d == filesize = %ld\n", wav_header->wav_size+8, filesize);
	printf("fmt_chunk_size = %d\n", wav_header->fmt_chunk_size);
	printf("audio_format = %hd\n", wav_header->audio_format);
	printf("num_channels = %hd\n", wav_header->num_channels);
	printf("sample_rate = %d\n", wav_header->sample_rate);
	printf("byte_rate = %d\n", wav_header->byte_rate);
	printf("sample_alignment = %hd\n", wav_header->sample_alignment);
	printf("bit_depth = %hd\n", wav_header->bit_depth);
	short bytes_per_sample = wav_header->bit_depth / 8;
	printf("data_bytes = %d\n", wav_header->data_bytes);
	long num_samples = wav_header->data_bytes / bytes_per_sample;
	printf("end_of_header (offset) at 0x%0X\n", sizeof(wav_header_type));
	if (wav_header->audio_format==PCM_FORMAT && wav_header->bit_depth==16)
		use_pcm_16bit(filename, (int16_t*)(memoryblock+sizeof(wav_header_type)), num_samples);
	else
		fprintf(stderr, "ERROR: unsupported wav format\n");
	// is there a trailer?
	long bytes_before_trailer = sizeof(wav_header_type) + wav_header->data_bytes;
	printf("bytes_before_trailer = %ld\n", bytes_before_trailer);
	byte *address_after_samples = memoryblock + bytes_before_trailer;
	int trailer_size = filesize - bytes_before_trailer;
	printf("trailer_size = %d\n", trailer_size);
	if (DEBUG) hexdump(address_after_samples, trailer_size);
	if (trailer_size>=0)
		check_wav_trailer(address_after_samples, trailer_size);
} // check_wav_structure

// see lecture 20210128
int open_wav_file(char *filename) {
	if (DEBUG) printf("open_wav_filename(\"%s\")\n", filename);
	FILE *fp = NULL;
	if (fp = fopen(filename,"rb")) { // read binary
		if (DEBUG) printf("open_wav_filename(\"%s\") - open success\n", filename);
		unsigned long filesize = get_filesize(fp);
		if (DEBUG) printf("open_wav_filename(\"%s\") - filesize=%ld Bytes\n", filename, filesize);
		// let's allocate memory for it:
		byte *memoryblock = (byte *)malloc(filesize); // get dynamic memory
		if (memoryblock == NULL) { // failed
			fprintf(stderr, "ERROR: cannot allocate memory for \"%s\"\n", filename);
			perror("Reason"); // OS tells us why it failed ... see "errno -l" on Linux
			return EXIT_FAILURE;
		}
		// it is a binary file, so let's transfer it:
		size_t rv = fread(memoryblock, sizeof(byte), filesize, fp);
		if (rv < filesize) { // reading did not work
			fprintf(stderr, "ERROR: cannot read enough from file \"%s\"\n", filename);
			perror("Reason"); // OS tells us why it failed ... see "errno -l" on Linux
		} else { // OK
			// We can close the file here, because we have its contents in memory now.
			fclose(fp);
			int hexdumpsize = (filesize < 256) ? filesize : 256; // shorten output
			hexdump(memoryblock, hexdumpsize);
			check_wav_structure(filename, memoryblock, filesize);
		}
		free(memoryblock);
	} else {
		fprintf(stderr, "ERROR: cannot open file \"%s\"\n", filename);
		perror("Reason"); // OS tells us why it failed ... see "errno -l" on Linux
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
} // open_wav_file

/*************************** MAIN ************************/
#define FILENAME_MAXSTRLEN 64
// int main() { // Standard way so far
int main(int argc, char **argv) { // professional way
	for (int argnum = 0; argnum < argc; argnum++) { // process command line arguments
		// command line switch
		if (strcmp(argv[argnum], "-d") == 0) { DEBUG = 1; arg_list_start_index = argnum + 1; }
		if (DEBUG) printf("argv[%d]=\"%s\"\n", argnum, argv[argnum]);
	}
	char filename[FILENAME_MAXSTRLEN]; // used for all files later
	int rv; // return value for various function calls.
	if (1) { // Lab6 2021.02.03
		DEBUG = 1;
		flag_hexdump_real_address_print = 0; // relative address starting with 0x00.
		//if (DEBUG) printf("wav_header_template=\n");
		//hexdump(&wav_header_template,sizeof(wav_header_template));
		//char filenames[][FILENAME_MAXSTRLEN] = {"sine_440hz"};
		char filenames[][FILENAME_MAXSTRLEN] = {
			"sine_440hz","metronome_120bpm","rect_sweep_5s",
			"multitone_haw_hamburg","multitone_0123456789",
			"white_noise","pink_noise","brown_noise","silence"};
		int file_count = sizeof(filenames) / FILENAME_MAXSTRLEN;
		// iterate over all given files and show its contents
		if (0) { // only if we want to see this
			for (int i = 0; i < file_count; i++) {
				strcpy(filename, filenames[i]);
				strcat_s(filename, FILENAME_MAXSTRLEN, ".wav"); // append extension
				if (DEBUG) printf("filename=\"%s\"\n", filename);
				rv = open_wav_file(filename);
				if (rv) return rv; // Error -> exit
				//if (DEBUG) _sleep(1000); // a break of one second
				// if this ^ doesn't compile, just comment out the whole line.
			}
		}
		printf("\n\n");
		printf("***************************************************\n");
		printf("Student code:\n");
		printf("***************************************************\n");
		/* Dear Student, here you put your own code according to the task list: */
		// Task 1a: Put your name into a string variable:
		char student_name[] = ""; // put your name in here
		// Task 1b: Put your immatriculation_number into a variable:
		unsigned int immatriculation_number = 0; // put your own number in here
		char better_ascii_student_name[FILENAME_MAXSTRLEN]="";
		// Task 2: implement this function clean_string() which replaces spaces with "_"
		//         and converts all uppercase letters to lowercase.
		//         The result must only contain the chars "_" or "a-z".
		clean_string(student_name, better_ascii_student_name);
		if (!strcmp(student_name, "") || immatriculation_number <= 2000000) {
			fprintf(stderr, "ERROR: Wrong name and/or number provided!\n"); exit(EXIT_FAILURE);
		} else { // don't change this!
			printf("(Mockup) Exam code of student \"%s\" (%u) -> %s\n",
				student_name, immatriculation_number, better_ascii_student_name);
			int idx = immatriculation_number % 8;
			strcpy(filename, filenames[idx]);
			strcat_s(filename, FILENAME_MAXSTRLEN, ".wav"); // append extension
			printf("Using file#%d \"%s\"\n", idx, filenames);
		}
		printf("\nHere comes my own code:\n");

		// Task 3: Take a little time to understand the program, run it and observe its output.
		// Hint: This is based on the code of lecture 20210128, which you should have checked by now.
		// So you are now able to load a WAV file into memory, great!
		// As you have seen, the following function calls happen in a sequence:
		// open_wav_file() -> check_wav_structure() -> use_pcm_16bit(), check_wav_trailer()
		// Task 4: Implement plot_samples() called from inside use_pcm_16bit().
		//         This should be done with ASCII chars ('*') on the console output.
		//         For simplicity use time (axis) from top to bottom
		//         We should see the amplitude of one sample in one row such that
		//         the X-position is proportional to the amplitude. Like in a previous lab.
		//         Example:
		//         *
		//                            *
		//                                                *
		//                            *
		//         *
		//                            *
		// Task 4:
		student_has_implemented.task4 = 0; // change this to 1 if you are working on it.
		if (student_has_implemented.task4) {
			rv = open_wav_file(filename); // this will call your function plot_samples()
			if (rv) return rv; // Error -> exit
		}

		// Task 5: Write the ASCII plot into a text file (instead of STDOUT like above)
		//         Use the base filename, but with extension .txt
		// Attention: You must change this filename (inside your function)
		//         before writing to it,
		//         otherwise you destroy the original .wav file!
		//         You put your code into the function plot_samples_into_file()
		// Task 5: 
		student_has_implemented.task5 = 0; // change this to 1 if you are working on it.
		if (student_has_implemented.task5) {
			rv = open_wav_file(filename); // this will call your function plot_samples()
			if (rv) return rv; // Error -> exit
		}

		// Task 6: Now create a binary file.
		//         Implement write_binary_file_generic(filename, buffer_for_test, filesize)
		//         The data content should come from a generic buffer (address given, size=filesize).
		// Task 6:
		student_has_implemented.task6 = 0; // change this to 1 if you are working on it.
		if (student_has_implemented.task6) {
			char binfilename[FILENAME_MAXSTRLEN]; // uninitialized memory
			strcpy(binfilename, better_ascii_student_name);
			strcat(binfilename, ".bin");
			int buffer_for_test[10]; int filesize = 40;
			rv = write_binary_file_generic(binfilename, buffer_for_test, filesize);
			if (rv) return rv; // Error -> exit
			// you could verify the output file with a hex editor software, if you want.
		}

		// Task 7: Now we create our own WAV file!
		//         The file name will be your better_ascii_student_name with extension .wav
		//         We use function write_wav_file_empty() above
		//         Inside we create a "WAV Header" first, leave data empty for now.
		//         We don't need the WAV trailer, just the header is enough.
		// Task 7: 
		student_has_implemented.task7 = 0; // change this to 1 if you are working on it.
		char wavfilename[FILENAME_MAXSTRLEN]; // will be used below
		if (student_has_implemented.task7) {
			strcpy(wavfilename, better_ascii_student_name);
			strcat(wavfilename, "_0.wav");
			rv = write_wav_file_empty(wavfilename);
			if (rv) return rv; // Error -> exit
		}

		// Task 8: Now we fill that WAV file with a sine wave.
		//         We use function write_wav_file_sinewave() above.
		//         Let the duration be 3 seconds.
		//         The frequency is given below as function argument.
		//         You can try out playing audio of the resulting file on your system.
		// Task 8: 
		student_has_implemented.task8 = 0; // change this to 1 if you are working on it.
		if (student_has_implemented.task8) {
			strcpy(wavfilename, better_ascii_student_name);
			strcat(wavfilename, "_1.wav");
			double duration = 3.0;
			double frequency = 1000.0; // Hz
			rv = write_wav_file_sinewave(wavfilename, frequency, duration);
			if (rv) return rv; // Error -> exit
		}

		// Task 9: Now we create a WAV file playing one octave of musical notes.
		//         We use function write_wav_file_octave() above.
		//         Let the duration be 0.5 seconds per note.
		//         The start frequency is given below as function argument.
		//         You can try out playing audio of the resulting file on your system.
		// Task 9: 
		student_has_implemented.task9 = 0; // change this to 1 if you are working on it.
		if (student_has_implemented.task9) {
			strcpy(wavfilename, better_ascii_student_name);
			strcat(wavfilename, "_2.wav");
			double duration = 0.5;
			double frequency = 261.63; // 261.63 Hz for musical note C
			rv = write_wav_file_octave(wavfilename, frequency, duration);
			if (rv) return rv; // Error -> exit
		}

		// Task 10: Now we create a WAV file playing a melody.
		//         We use function write_wav_file_melody() above.
		//         The start frequency is given below as function argument.
		//		   The melody is given as an array of struct musical_note
		//         You can try out playing audio of the resulting file on your system.
		// Task 10: 
		student_has_implemented.task10 = 0; // change this to 1 if you are working on it.
		if (student_has_implemented.task10) {
			strcpy(wavfilename, better_ascii_student_name);
			strcat(wavfilename, "_3.wav");
			double f = 440.0; // 440.0 Hz for musical note A
			double b = pow(2.0, 1.0 / 12.0); // base of power b^n
			double d = 0.5; // duration of one note
			tMelody melody = { 15, {
				{f*pow(b,0),d}, // A
				{f*pow(b,0),d}, // A
				{f*pow(b,1),d}, // Bb
				{f*pow(b,3),d}, // C
				{f*pow(b,3),d}, // C
				{f*pow(b,1),d}, // Bb
				{f*pow(b,0),d}, // A
				{f*pow(b,-2),d}, // G
				{f*pow(b,-4),d}, // F
				{f*pow(b,-4),d}, // F
				{f*pow(b,-2),d}, // G
				{f*pow(b,0),d}, // A
				{f*pow(b,0),1.5*d}, // A
				{f*pow(b,-2),0.5*d}, // G
				{f*pow(b,-2),1.5*d}, // G
			} };
			rv = write_wav_file_melody(wavfilename, melody);
			if (rv) return rv; // Error -> exit
		}
	}
	return 0;
} // main
