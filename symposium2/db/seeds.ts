import { generateRandomHexColor } from "src/core/utils"
import { Chance } from "chance"
import db from "./index"
import _ from "lodash"

const seed = async () => {
  const chance = new Chance()

  const cat1 = await db.category.create({
    data: {
      name: "Tech",
      color: generateRandomHexColor(),
    },
  })
  const cat2 = await db.category.create({
    data: {
      name: "Music",
      color: generateRandomHexColor(),
    },
  })
  const cat3 = await db.category.create({
    data: {
      name: "News",
      color: generateRandomHexColor(),
    },
  })

  const user = await db.user.create({
    data: {
      email: chance.email(),
    },
  })

  for (let i = 0; i < 100; i++) {
    await db.thread.create({
      data: {
        title: chance.sentence(),
        creator: {
          connect: {
            id: user.id,
          },
        },
        category: {
          connect: {
            id: _.sample([cat1.id, cat2.id, cat3.id]),
          },
        },
      },
    })
  }
}

export default seed
