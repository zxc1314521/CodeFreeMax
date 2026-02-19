import {
  j as s,
  d as a,
  r as c,
  Y as m
} from "./ErrorMessage-sgZuVxCg.js";

function d({
  power: e,
  onClick: t
}) {
  const {
    author: i,
    description: n,
    displayName: o,
    iconUrl: r,
    name: l
  } = e;
  return s.jsxs("div", {
    className: "powers-list-item",
    onClick: () => {
      t({
        name: l
      })
    },
    children: [s.jsx("div", {
      className: `powers-list-item-icon${r?" powers-list-item-icon--img":""}`,
      children: r ? s.jsx("img", {
        src: r
      }) : s.jsx(a, {
        type: "powers"
      })
    }), s.jsxs("div", {
      className: "powers-list-item-content",
      children: [s.jsx("div", {
        className: "powers-list-item-name",
        children: o || l
      }), s.jsx("div", {
        className: "powers-list-item-description",
        children: n
      }), s.jsxs("div", {
        className: "powers-list-item-author",
        children: ["by", s.jsx("span", {
          children: i
        })]
      })]
    })]
  })
}

function p() {
  const {
    callApi: e
  } = c.useContext(m);
  return {
    handleClick: c.useCallback(({
      name: i
    }) => {
      e("viewPowerDetails", {
        name: i
      })
    }, [e])
  }
}

function h({
  firstItem: e,
  powers: t
}) {
  const {
    handleClick: i
  } = p();
  return s.jsxs("div", {
    className: "powers-list",
    children: [e, t.map(n => s.jsx(d, {
      power: n,
      onClick: i
    }, n.name))]
  })
}
export {
  h as P
};