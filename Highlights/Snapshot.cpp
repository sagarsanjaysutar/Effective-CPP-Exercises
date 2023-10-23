#include <gst/gst.h>

class SourcePipeline {
public:
    SourcePipeline() {
        // Initialize GStreamer
        gst_init(nullptr, nullptr);

        // Create elements
        videoSource = gst_element_factory_make("v4l2src", "video-source");
        capsFilter = gst_element_factory_make("capsfilter", "caps-filter");
        videoConvert = gst_element_factory_make("videoconvert", "video-convert");
        x264Enc = gst_element_factory_make("x264enc", "x264-encoder");
        interpipeSink = gst_element_factory_make("interpipesink", "source-sink");

        if (!videoSource || !capsFilter || !videoConvert || !x264Enc || !interpipeSink) {
            g_print("Failed to create elements.\n");
            return;
        }

        // Create the pipeline
        pipeline = gst_pipeline_new("source-pipeline");

        // Add elements to the pipeline
        gst_bin_add_many(GST_BIN(pipeline), videoSource, capsFilter, videoConvert, x264Enc, interpipeSink, nullptr);

        // Set properties on interpipesink
        g_object_set(G_OBJECT(interpipeSink), "name", "source", nullptr);

        // Link the elements
        if (gst_element_link_many(videoSource, capsFilter, videoConvert, x264Enc, interpipeSink, nullptr) != TRUE) {
            g_print("Failed to link elements.\n");
            return;
        }

        // Set the pipeline to the playing state
        gst_element_set_state(pipeline, GST_STATE_PLAYING);
    }

    ~SourcePipeline() {
        // Set the pipeline to the null state and release resources
        gst_element_set_state(pipeline, GST_STATE_NULL);
        gst_object_unref(pipeline);
    }

private:
    GstElement* pipeline;
    GstElement* videoSource;
    GstElement* capsFilter;
    GstElement* videoConvert;
    GstElement* x264Enc;
    GstElement* interpipeSink;
};

class SinkPipeline {
public:
    SinkPipeline() {
        // Initialize GStreamer
        gst_init(nullptr, nullptr);

        // Create elements
        interpipeSrc = gst_element_factory_make("interpipesrc", "interpipe-source");
        queue = gst_element_factory_make("queue", "queue");
        h264Parse = gst_element_factory_make("h264parse", "h264-parser");
        avdecH264 = gst_element_factory_make("avdec_h264", "avdec-h264");
        jpegEnc = gst_element_factory_make("jpegenc", "jpeg-encoder");
        fileSink = gst_element_factory_make("filesink", "file-sink");

        if (!interpipeSrc || !queue || !h264Parse || !avdecH264 || !jpegEnc || !fileSink) {
            g_print("Failed to create elements.\n");
            return;
        }

        // Create the pipeline
        pipeline = gst_pipeline_new("sink-pipeline");

        // Add elements to the pipeline
        gst_bin_add_many(GST_BIN(pipeline), interpipeSrc, queue, h264Parse, avdecH264, jpegEnc, fileSink, nullptr);

        // Set properties on interpipesrc
        g_object_set(G_OBJECT(interpipeSrc), "listen-to", "source", "is-live", true, nullptr);

        // Set the file location property for filesink
        g_object_set(G_OBJECT(fileSink), "location", "/home/ssutar/Desktop/x.jpg", nullptr);

        // Link the elements
        if (gst_element_link_many(interpipeSrc, queue, h264Parse, avdecH264, jpegEnc, fileSink, nullptr) != TRUE) {
            g_print("Failed to link elements.\n");
            return;
        }

        // Set the pipeline to the playing state
        gst_element_set_state(pipeline, GST_STATE_PLAYING);
    }

    ~SinkPipeline() {
        // Set the pipeline to the null state and release resources
        gst_element_set_state(pipeline, GST_STATE_NULL);
        gst_object_unref(pipeline);
    }

private:
    GstElement* pipeline;
    GstElement* interpipeSrc;
    GstElement* queue;
    GstElement* h264Parse;
    GstElement* avdecH264;
    GstElement* jpegEnc;
    GstElement* fileSink;
};

int main(int argc, char* argv[]) {
    // Create and run the source pipeline
    SourcePipeline sourcePipeline;

    // Create and run the sink pipeline
    SinkPipeline sinkPipeline;

    // Main loop or other application logic can go here

    return 0;
}
