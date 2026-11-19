#ifndef _R_COMMON_C_ALSA_SEQ_LISTENER_H
#define _R_COMMON_C_ALSA_SEQ_LISTENER_H

#include <alsa/asoundlib.h>
#include <pthread.h>
#include <stdint.h>

typedef void (*alsa_seq_listener_recv_t)(void *, const snd_seq_event_t *, const unsigned char *, int);

typedef struct
{
	snd_seq_t *seq;
	snd_midi_event_t *decoder;
	alsa_seq_listener_recv_t receiver;
	void *context;
} alsa_seq_listener_t;

void alsa_seq_listener_debug_receiver(void *context, const snd_seq_event_t *event,
	const unsigned char *data, int data_n);

void *alsa_seq_listener_thread(void *PTR);

pthread_t alsa_seq_listener(snd_seq_t *seq, snd_midi_event_t *decoder,
	alsa_seq_listener_recv_t receiver, void *context);

#endif
