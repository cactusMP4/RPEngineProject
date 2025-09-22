#include "Layer.h"

#include <algorithm>

namespace rpe {
    Layer::Layer (const std::string& name) : debugName(name) {

    }
    Layer::~Layer() {

    }


    LayerStack::LayerStack() {
        LayerInsert = Layers.begin();
    }
    LayerStack::~LayerStack() {
        for (const Layer* layer : Layers) {
            delete layer;
        }
    }

    //making sure layers always go before overlays
    void LayerStack::PushLayer(Layer *layer) {
        LayerInsert = Layers.emplace(LayerInsert, layer);
        layer->Attach();
    }
    void LayerStack::PopLayer(Layer *layer) {
        auto it = std::find(Layers.begin(), Layers.end(), layer);
        if (it != Layers.end()) {
            Layers.erase(it);
            --LayerInsert;
        }
        layer->Detach();
    }

    void LayerStack::PushOverlay(Layer *overlay) {
        Layers.emplace_back(overlay);
        overlay->Attach();
    }
    void LayerStack::PopOverlay(Layer *overlay) {
        auto it = std::find(Layers.begin(), Layers.end(), overlay);
        if (it != Layers.end()) {
            Layers.erase(it);
        }
        overlay->Detach();
    }
}
