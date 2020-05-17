#pragma once

namespace detail {

struct property_common_base {
};

template <typename T>
struct property_base : property_common_base {
private:
  T t_;

  property_common_base* observer_;

  void notify() {
    if (observer_ != nullptr) {
      static_cast<property_base<T>*>(observer_)->update_from(this);
    }
  }
  
  void update_from(property_base<T> *src) {
    t_ = src->t_;
  }

protected:
  template <typename U> void set(U const &u) {
    t_ = u;
    notify();
  }

  T const &get() const {
    return t_;
  }

  void connect(property_base<T> * observer, bool both_ways = false) {
    observer_ = observer;
    observer->t_ = t_;

    if (both_ways) {
      observer->connect(this, false);
    }
  }
};

} // namespace detail

template <typename T> struct ro_property : public detail::property_base<T> {
private:
  typedef detail::property_base<T> base_t;
public:
  T const &get() {
    return base_t::get();
  }
};

template <typename T> struct property : public detail::property_base<T> {
private:
  typedef detail::property_base<T> base_t;
public:
  template <typename U> void set(U const &u) {
    base_t::set(u);
  }

  T const &get() {
    return base_t::get();
  }

  void connect(property<T>* dst) {
    base_t::connect(dst);
  }

  void connect_bi(property<T>* dst) {
    base_t::connect(dst, true);
  }

  void connect(ro_property<T>* dst) {
    base_t::connect(dst);
  }
};

