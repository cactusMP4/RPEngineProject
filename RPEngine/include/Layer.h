#pragma once

#include "Core.h"
#include "Event.h"

namespace rpe {
    class RPE_API Layer {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer();

        virtual void Attach() {}
        virtual void Detach() {}
        virtual void Update() {}
        virtual void OnEvent(Event& event) {}

        const std::string& GetName() const { return debugName; }

    protected:
        std::string debugName;
    };

    class LayerStack {
    public:
        LayerStack();
        ~LayerStack();

        void PushLayer(Layer* layer);
        void PopLayer(Layer* layer);

        void PushOverlay(Layer* layer);
        void PopOverlay(Layer* layer);

        std::vector<Layer*>::iterator begin() { return Layers.begin(); }
        std::vector<Layer*>::iterator end() { return Layers.end(); }
    private:
        std::vector<Layer*> Layers;
        std::vector<Layer*>::iterator LayerInsert;
    };
}
