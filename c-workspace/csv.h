int32_t ReadCSV(char * filename, time_t **t, uint16_t **mic);
void WriteHeaders(char * filename);
void AppendZrain(char * filename, int32_t time, int32_t v1, int32_t v2, int32_t v3, int32_t v4);
