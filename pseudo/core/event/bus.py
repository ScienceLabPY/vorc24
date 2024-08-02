from event_t import EventType

class EventBus:
    def __init__(self):
        self.subscribers = {}
    
    def subscribe(self, event_type: EventType, handler):
        if event_type not in self.subscribers:
            self.subscribers[event_type] = []
        self.subscribers[event_type].append(handler)
    
    def publish(self, event):
        if event.type in self.subscribers:
            for handler in self.subscribers[event.type]:
                handler.handle(event)