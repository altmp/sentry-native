#ifndef SENTRY_TRACING_H_INCLUDED
#define SENTRY_TRACING_H_INCLUDED

#include "sentry_boot.h"
#include "sentry_value.h"

/**
 * A span.
 */
typedef struct sentry_span_s {
    sentry_value_t inner;
    // The transaction the span is contained in.
    sentry_transaction_t *transaction;
} sentry_span_t;

/**
 * A transaction context.
 */
typedef struct sentry_transaction_context_s {
    sentry_value_t inner;
} sentry_transaction_context_t;

/**
 * A transaction.
 */
typedef struct sentry_transaction_s {
    sentry_value_t inner;
} sentry_transaction_t;

void sentry__transaction_context_free(sentry_transaction_context_t *tx_cxt);

sentry_transaction_t *sentry__transaction_new(sentry_value_t inner);
void sentry__transaction_incref(sentry_transaction_t *tx);
void sentry__transaction_decref(sentry_transaction_t *tx);

sentry_value_t sentry__value_span_new(size_t max_spans, sentry_value_t parent,
    char *operation, char *description);
sentry_span_t *sentry__span_new(
    sentry_transaction_t *parent_tx, sentry_value_t inner);
void sentry__span_free(sentry_span_t *span);

/**
 * Returns an object containing tracing information extracted from a
 * transaction (/span) which should be included in an event.
 * See https://develop.sentry.dev/sdk/event-payloads/transaction/#examples
 */
sentry_value_t sentry__transaction_get_trace_context(
    sentry_transaction_t *span);

#endif