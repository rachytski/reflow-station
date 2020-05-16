#pragma once

struct property_base;

typedef property_base* property_base_ptr;

struct property_base {
protected:      
  property_base* observer_ = nullptr;

  void connect(property_base *observer) {
    observer_ = observer;
  }

  void notify() {
    if (observer_ != nullptr) {
      observer_->update_from(this);
    }
  }

  virtual void update_from(property_base* src) = 0;
};

template <typename T> struct property : property_base {
private:
  T t_;

  virtual void update_from(property_base *src) {
    t_ = static_cast<property<T>*>(src)->t_;
  }
  
public:  
  template <typename U> void set(U const &u) {
    t_ = u;
    notify();
  }

  T const &get() const {
    return t_;
  }

  virtual void connect(property<T> * observer, bool both_ways = false) {
    property_base::connect(static_cast<property_base*>(observer));
    observer->t_ = t_;
    
    if (both_ways) {
      observer->connect(this, false);
    }
  }
};
